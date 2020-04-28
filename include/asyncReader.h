//
// Created by kekor on 28.04.2020.
//

#include <thread>
#include <functional>
#include <sys/stat.h>

#include "../include/cache.h"
#include "../include/response.h"
#include "../include/blockQueue.hpp"

#ifndef TEST_STRACE_AYNCREADER_H
#define TEST_STRACE_AYNCREADER_H

class AsyncReader {
public:
    typedef std::function<void(std::unique_ptr<Response>)> callback_type;
    typedef std::pair<std::unique_ptr<Response>, callback_type> pair_type;
    typedef std::unique_ptr<pair_type> uptr_pair_type;

    AsyncReader();
    void push(std::unique_ptr<Response> response, callback_type callback);
private:
    static void _reader(AsyncReader* thisObject);

    int _fileSize(int fd);

    BlockQueue<uptr_pair_type> _readQueue;
    Cache _cache;
};

#endif //TEST_STRACE_AYNCREADER_H
