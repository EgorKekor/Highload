//
// Created by kekor on 28.04.2020.
//


#include "../include/asyncReader.h"

void AsyncReader::push(std::unique_ptr<Response> response, AsyncReader::callback_type callback) {
    if (response->isFast) {
        callback(std::move(response));
        return;
    }

    auto elem = std::make_unique<pair_type>(std::move(response), std::move(callback));
    _readQueue.push(std::move(elem));
}

AsyncReader::AsyncReader() {
//    std::thread workerThr(_reader, this);
//    workerThr.detach();
}

void AsyncReader::_reader(AsyncReader *thisObject) {
    for(;;) {
        auto pair_ptr = std::move(thisObject->_readQueue.blockPeek());



        thisObject->_readQueue.blockPop();
        break;//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    }
}

int AsyncReader::_fileSize(int fd) {
    struct stat stat_buf;
    int rc = fstat(fd, &stat_buf);
    return rc == 0 ? stat_buf.st_size : -1;
}
