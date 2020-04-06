//
// Created by kekos on 06.04.2020.
//

#ifndef HIGHLOAD_CONVEYORPART_HPP
#define HIGHLOAD_CONVEYORPART_HPP

#include <iostream>
#include <queue>

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
private:
    bool _blocked = false;
    std::queue<T> _queue;
    std::condition_variable_any _haveData;
    std::mutex _haveDataMutex;
};


template<class T>
void BlockQueue<T>::push(const T &value) {
    _queue.push(value);
    if (_blocked) {
        _haveData.notify_all();
    }
}

template<class T>
void BlockQueue<T>::push(T &&value) {
    _queue.push(std::move(value));
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
        _haveDataMutex.lock();
        _haveData.wait(_haveDataMutex);
        _blocked = false;
        _haveDataMutex.unlock();
    }
    return _queue.front();
}

template<class T>
void BlockQueue<T>::pop() {
    _queue.pop();
}

template<class T>
void BlockQueue<T>::blockPop() {
    if (_queue.size() == 0) {
        _blocked = true;
        _haveDataMutex.lock();
        _haveData.wait(_haveDataMutex);
        _blocked = false;
        _haveDataMutex.unlock();
    }
    _queue.pop();
}

//  ===================================================
//  ===================================================

template <class INP_CONT, class OUT_CONT>
class ConveyorPart {
public:
    using THIS_OBJECT_UNIQUE_PTR = std::unique_ptr<ConveyorPart<INP_CONT, OUT_CONT>>;
    using THIS_OBJECT_TYPE = ConveyorPart<INP_CONT, OUT_CONT>;

    ConveyorPart(
            std::shared_ptr<INP_CONT> input,
            std::shared_ptr<OUT_CONT> output,
            std::function<void(THIS_OBJECT_UNIQUE_PTR)> conveyorWorker) :
    input(input),
    output(output) {
        std::thread workerThr(conveyorWorker, THIS_OBJECT_UNIQUE_PTR(this));
        workerThr.detach();
    };

    std::shared_ptr<INP_CONT> input;
    std::shared_ptr<OUT_CONT> output;
};



#endif //HIGHLOAD_CONVEYORPART_HPP
