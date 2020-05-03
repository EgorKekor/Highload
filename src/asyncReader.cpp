//
// Created by kekor on 28.04.2020.
//


#include <fcntl.h>
#include "../include/asyncReader.h"

extern Config* config;

char* testBuf = nullptr;

void AsyncReader::push(std::unique_ptr<Response> response, AsyncReader::callback_type callback) {
    auto bodyPtr = _cache.get(response->filename);
    if (bodyPtr->getAdress() == nullptr) {
        std::cout << "Response from disk" << std::endl;
        auto elem = std::make_unique<pair_type>(std::move(response), std::move(callback));
        _readQueue.push(std::move(elem));
    } else {
        std::cout << "Response from cache" << std::endl;
        response->putBody(bodyPtr);
        callback(std::move(response));
    }
}


AsyncReader::AsyncReader() {
    auto err = io_setup(_maxSize, &ctx);
    if (err < 0) {
        throw std::runtime_error("AsyncRead: io_setup error");
    }

    std::thread workerThr(_manager, this);
    workerThr.detach();

    std::thread readerThr(_asyncReader, this);
    readerThr.detach();
}

void AsyncReader::_manager(AsyncReader *thisObject) {
    for(;;) {
        auto *readPack = new ReadPack();    // Warning, possible memleak!

        readPack->add(std::move(thisObject->_readQueue.blockPeek()));
        thisObject->_readQueue.blockPop();

        size_t amount = 1;
        while (!thisObject->_readQueue.isVoid() && (amount < MAX_FILES_BLOCK)) {
            readPack->add(std::move(thisObject->_readQueue.blockPeek()));
            thisObject->_readQueue.blockPop();
            amount++;
        }

        if (!readPack->submit(&thisObject->ctx)) {
        }
    }
}

void AsyncReader::_asyncReader(AsyncReader *thisObject) {
    struct io_event *events = new struct io_event[1];
    for(;;) {
        auto amount = io_getevents(thisObject->ctx, 1, 1, events, nullptr);
        if (amount < 0) {
            std::cerr << "AsyncRead: io_getevents error" << std::endl;
            continue;
        }

        auto *readPackResult = reinterpret_cast<ReadPack::ReadPackResult*>(events[0].data);
        auto *readPack = readPackResult->object;
        bool res = thisObject->_cache.put(readPack->getFilename(readPackResult->position), readPack->getBody(readPackResult->position));
        readPack->complite(readPackResult->position, &events[0]);
        if (readPack->isEnded()) {
            delete readPack;
            readPack = nullptr;
            readPackResult = nullptr;
        }

    }
}

// ======================================================

ReadPack::ReadPack() : _size(0), _capacity(MAX_FILES_BLOCK) {
    memset(_iocbs, 0, _capacity * sizeof(struct iocb));

    if (_holders.capacity() < _capacity) {
        _holders.reserve(_capacity);
    }

    for (int i = 0; i < _capacity; ++i) {
        _returns[i].object = this;
        _returns[i].position = i;
    }
}

ReadPack::~ReadPack() {}

bool ReadPack::add(AsyncReader::uptr_pair_type ptr) {
    int fd = open(ptr->first->filename.c_str(), O_RDONLY | O_DIRECT);
    size_t size = ptr->first->fileSize();

    if (_size == _capacity - 1) {
        return false;
    }

    size_t align = config->getAlign();
    size_t allocSize = align + size / align;
    size_t length = size;
    size = allocSize;

    char* buf = static_cast<char*>(aligned_alloc(align, allocSize));
    if (buf == nullptr) {
        std::cerr << "Ooops!" << std::endl;
        return false;
    }
    ptr->first->putBody(std::move(std::make_shared<Body>(buf, length, size)));
    _holders.emplace_back(std::move(ptr));

    _iocbs[_size].aio_data = reinterpret_cast<__u64>(&_returns[_size]); // Index of _returns
    _iocbs[_size].aio_lio_opcode = IOCB_CMD_PREAD;
    _iocbs[_size].aio_fildes = static_cast<__u32>(fd);
    _iocbs[_size].aio_buf = reinterpret_cast<__u64>(_holders.back()->first->getBody()->getAdress());
    _iocbs[_size].aio_nbytes = size;

    _iocb_list[_size] = &_iocbs[_size];

    _size++;
    return true;
}

bool ReadPack::submit(aio_context_t *ctx) {
    auto err = io_submit(*ctx, _size, _iocb_list);
    return err >= 0;
}

bool ReadPack::complite(size_t index, struct io_event *event) {
    if (_complites == _size) {
        return false;
    }
    _complites++;


    AsyncReader::callback_type callback(std::move( _holders[index]->second));
    callback(std::move(_holders[index]->first));
    return true;
}

std::shared_ptr<Body> &ReadPack::getBody(int index) {
    return _holders[index]->first->getBody();
}

std::string &ReadPack::getFilename(int index) {
    return _holders[index]->first->filename;
}

