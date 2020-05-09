//
// Created by kekos on 07.04.2020.
//

#ifndef HIGHLOAD_BLOCKQUEUE_HPP
#define HIGHLOAD_BLOCKQUEUE_HPP

#include <iostream>
#include <deque>
#include <condition_variable>
#include <cassert>
#include <thread>


template <class T>
class BlockQueue {
public:
    BlockQueue() = default;
    void push( const T& value );
    void push( T&& value );

    T& peek();
    T& blockPeek();
    void pop();
    void blockPop();
    size_t size() { return _queue.size(); };
    bool isVoid() { return _queue.size() == 0; };
private:
    bool _blocked = false;
    std::deque<T> _queue;
    std::condition_variable _haveData;
    std::mutex _haveDataMutex;
    std::mutex _operation;
};


template<class T>
void BlockQueue<T>::push(const T &value) {
//    if (_queue.size() > 10) {
//        std::this_thread::yield();
//    }
    std::unique_lock<std::mutex> lock(_operation);
    _queue.push_back(value);
    if (_blocked) {
        _haveData.notify_all();
    }
}

template<class T>
void BlockQueue<T>::push(T &&value) {
//    if (_queue.size() > 10) {
//        std::this_thread::yield();
//    }
    std::unique_lock<std::mutex> lock(_operation);
    _queue.push_back(std::move(value));
    if (_blocked) {
        _haveData.notify_all();
    }
}

template<class T>
T &BlockQueue<T>::peek() {
    std::unique_lock<std::mutex> lock(_operation);
    T& val = _queue.front();
    return val;
}

template<class T>
T &BlockQueue<T>::blockPeek() {
    if (_queue.size() == 0) {
        _blocked = true;
        std::unique_lock<std::mutex> lock(_haveDataMutex);
        _haveData.wait(lock);
        _blocked = false;
    }
    std::unique_lock<std::mutex> lock(_operation);
    T& val = _queue.front();
    return val;
}

template<class T>
void BlockQueue<T>::pop() {
    std::unique_lock<std::mutex> lock(_operation);
    if (_queue.size() == 0) {
        return;
    }
    _queue.pop_front();
}

template<class T>
void BlockQueue<T>::blockPop() {
    if (_queue.size() == 0) {
        _blocked = true;
        std::unique_lock<std::mutex> lock(_haveDataMutex);
        _haveData.wait(lock);
        _blocked = false;
    }
    std::unique_lock<std::mutex> lock(_operation);
    _queue.pop_front();
}

#endif //HIGHLOAD_BLOCKQUEUE_HPP
