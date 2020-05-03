//
// Created by kekor on 28.04.2020.
//

#include <thread>
#include <functional>
#include <sys/stat.h>
#include <linux/aio_abi.h>
#include <sys/syscall.h>


#include "../include/response.h"
#include "../include/blockQueue.hpp"
#include "../include/fastList.hpp"
#include "../include/defines.h"
#include "../include/cache.h"

#ifndef TEST_STRACE_AYNCREADER_H
#define TEST_STRACE_AYNCREADER_H

inline static int io_setup(unsigned nr, aio_context_t *ctxp) {
    return syscall(__NR_io_setup, nr, ctxp);
}

inline static int io_destroy(aio_context_t ctx) {
    return syscall(__NR_io_destroy, ctx);
}

inline static int io_submit(aio_context_t ctx, long nr, struct iocb **iocbpp) {
    return syscall(__NR_io_submit, ctx, nr, iocbpp);
}

inline static int io_getevents(aio_context_t ctx, long min_nr, long max_nr,
                               struct io_event *events,
                               struct timespec *timeout) {
    return syscall(__NR_io_getevents, ctx, min_nr, max_nr, events, timeout);
}



class AsyncReader {
public:
    typedef std::function<void(std::unique_ptr<Response> response)> callback_type;
    typedef std::pair<std::unique_ptr<Response>, callback_type> pair_type;
    typedef std::unique_ptr<pair_type> uptr_pair_type;

    AsyncReader();
    void push(std::unique_ptr<Response> response, callback_type callback);
private:
    static void _manager(AsyncReader* thisObject);
    static void _asyncReader(AsyncReader* thisObject);

    BlockQueue<uptr_pair_type> _readQueue;
    Cache _cache;

    aio_context_t ctx = 0;
    size_t _maxSize = IOCB_SIZE;
};



class ReadPack {
public:
    typedef struct ret {
        ReadPack* object;
        size_t position;
    } ReadPackResult;

    ReadPack();
    ~ReadPack();

    std::shared_ptr<Body>& getBody(int index);
    std::string& getFilename(int index);

    bool add(AsyncReader::uptr_pair_type ptr);
    bool complite(size_t index, struct io_event *event);
    bool submit(aio_context_t *ctx);
    bool isEnded() { return _complites == _size; };
private:
    size_t _complites = 0;
    size_t _size = 0;
    size_t _capacity = 0;
    struct iocb* _iocb_list[MAX_FILES_BLOCK];
    struct iocb _iocbs[MAX_FILES_BLOCK];
    std::vector<AsyncReader::uptr_pair_type> _holders;

    struct ret _returns[MAX_FILES_BLOCK];
};

#endif //TEST_STRACE_AYNCREADER_H
