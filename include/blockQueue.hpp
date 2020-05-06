//
// Created by kekos on 07.04.2020.
//

#ifndef HIGHLOAD_BLOCKQUEUE_HPP
#define HIGHLOAD_BLOCKQUEUE_HPP

#include <iostream>
#include <deque>
#include <condition_variable>
#include <cassert>


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
    _operation.lock();
    _queue.push_back(value);
    if (_blocked) {
        _haveData.notify_all();
    }
    _operation.unlock();
}

template<class T>
void BlockQueue<T>::push(T &&value) {
    _operation.lock();
    _queue.push_back(std::move(value));
    if (_blocked) {
        _haveData.notify_all();
    }
    _operation.unlock();
}

template<class T>
T &BlockQueue<T>::peek() {
    _operation.lock();
    T& val = _queue.front();
    _operation.unlock();
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
    _operation.lock();
    T& val = _queue.front();
    _operation.unlock();
    return val;
}

template<class T>
void BlockQueue<T>::pop() {
    _operation.lock();
    if (_queue.size() == 0) {
        _operation.unlock();
        return;
    }
    _queue.pop_front();
    _operation.unlock();
}

template<class T>
void BlockQueue<T>::blockPop() {
    if (_queue.size() == 0) {
        _blocked = true;
        std::unique_lock<std::mutex> lock(_haveDataMutex);
        _haveData.wait(lock);
        _blocked = false;
    }
    _operation.lock();
    _queue.pop_front();
    _operation.unlock();

}

#endif //HIGHLOAD_BLOCKQUEUE_HPP
