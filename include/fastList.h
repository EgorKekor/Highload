//
// Created by kekor on 27.03.20.
//

#ifndef HIGHLOAD_LISTALLOCATOR_H
#define HIGHLOAD_LISTALLOCATOR_H

#include <cstddef>

template <class T> class FastListAllocator {
public:
    FastListAllocator();
    FastListAllocator(size_t size);
    ~FastListAllocator();

    T* _new();
    bool free(FastListAllocator<T> *node);

private:
    T *memory;
    size_t _size;
    size_t _head = 0;
    size_t _loading = 0;
    const size_t _min_size = 10000;
};



template <class T>
FastListAllocator<T>::FastListAllocator(size_t size) : _size(size) {
    memory = new T[_size];
    for (size_t i = 0; i < _size; ++i) {
        *((int*)&memory[i]) = (int)(i + 1);
    }
}

template <class T>
FastListAllocator<T>::FastListAllocator() : _size(_min_size) {
    memory = new T[_size];
    for (size_t i = 0; i < _size; ++i) {
        *((int*)&memory[i]) = (int)(i + 1);
    }
}

template <class T>
FastListAllocator<T>::~FastListAllocator() {
    delete [] memory;
}



template <class T>
T* FastListAllocator<T>::_new() {
    if (_loading == _size) {
        return nullptr;
    }

    _loading++;
    size_t next = (size_t)memory[_head];

    T* retVal = &memory[_head];
    _head = next;
    return retVal;
}


template <class T>
bool FastListAllocator<T>::free(FastListAllocator<T> *node) {
    *((size_t *)node) = _head;
    _head = //надо с адресами
}


//  ====================================================

template <class T> class Node {
public:
    Node() {};
    T &val;
    Node<T> *_next;
    Node<T> *_prev;
};




template <class T> class FastList {
public:
    FastList() : allocator() {
        _head = allocator._new();
        _tail = allocator._new();

        _head->_next = _tail;
        _head->_prev = nullptr;
        _tail->_prev = _head;
        _tail->_next = nullptr;
    };
    ~FastList() {};

    bool push(T &val);
    bool remove(Node<T> *node);

private:
    FastListAllocator<Node<T>> allocator;
    Node<T> *_head = nullptr;
    Node<T> *_tail = nullptr;
};


template <class T>
bool FastList<T>::push(T &val) {
    _tail->_next = allocator._new();
    _tail->_next->_prev = _tail;
    _tail->_next->next = nullptr;
    _tail = _tail->_next;
    return true;
}


template <class T>
bool FastList<T>::remove(Node<T> *node) {
    if ((node == _head) || (node == _tail)) {
        return false;
    }

    node->_prev->_next = node->_next;
    node->_next->_prev = node->_prev;

    allocator.free(node);
    return true;
}


#endif //HIGHLOAD_LISTALLOCATOR_H
