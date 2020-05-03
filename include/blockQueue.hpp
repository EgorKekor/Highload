//
// Created by kekos on 07.04.2020.
//

#ifndef HIGHLOAD_BLOCKQUEUE_HPP
#define HIGHLOAD_BLOCKQUEUE_HPP

#include <iostream>
#include <deque>
#include <condition_variable>


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
};


template<class T>
void BlockQueue<T>::push(const T &value) {
    _queue.push_back(value);
    if (_blocked) {
        _haveData.notify_all();
    }
}

template<class T>
void BlockQueue<T>::push(T &&value) {
    _queue.push_back(std::move(value));
    if (_blocked) {
        _haveData.notify_all();
    }
}

template<class T>
T &BlockQueue<T>::peek() {
    return _queue.front();
}

template<class T>
T &BlockQueue<T>::blockPeek() {
    if (_queue.size() == 0) {
        _blocked = true;
        std::unique_lock<std::mutex> lock(_haveDataMutex);
        _haveData.wait(lock);
        _blocked = false;
    }
    return _queue.front();
}

template<class T>
void BlockQueue<T>::pop() {
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
    _queue.pop_front();
}

#endif //HIGHLOAD_BLOCKQUEUE_HPP
