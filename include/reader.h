//
// Created by kekor on 27.03.20.
//

#ifndef HIGHLOAD_READER_H
#define HIGHLOAD_READER_H

#include <iostream>
#include <thread>
#include <map>
#include <condition_variable>
#include "../include/fastList.h"
#include "../include/stringHolder.h"
#include "../include/config.h"

class Reader {
public:
    Reader(size_t maxSockets = MAX_CONNECTIONS) :
            _socketPool(maxSockets),
            _holder(maxSockets),
        _started(false) {};
    ~Reader() {};
    bool start();
    bool push(SOCKET val);
    void block();
private:
    FastList<int> _socketPool;
    StringHolder _holder;

    std::condition_variable_any _haveData;
    std::mutex _haveDataMutex;
    bool _started;
    bool _blocked;
    static void _readLoop(Reader &instance);
};


#endif //HIGHLOAD_READER_H
