//
// Created by kekor on 27.03.20.
//

#ifndef HIGHLOAD_LISTALLOCATOR_H
#define HIGHLOAD_LISTALLOCATOR_H

#include <cstddef>
#include <functional>

#define MIN_SIZE    100

template <class T> class FastListAllocator {
public:
    typedef int*    pointer;

    FastListAllocator();
    FastListAllocator(size_t size);
    ~FastListAllocator();

    T* _new();
    bool free(T *node);

private:
    T *memory;
    T* _head = nullptr;
    size_t _size;
    size_t _loading = 0;
    const size_t _min_size = MIN_SIZE;

    void _init();
};

template <class T>
void FastListAllocator<T>::_init() {
    if (sizeof(T) < sizeof(pointer)) {
        throw std::runtime_error("FastListAllocator constructor: Wrong data type");
    }
    memory = new T[_size];
    _head = memory;
    for (size_t i = 0; i < _size - 1; ++i) {
        *((T**)(&memory[i])) = &memory[i + 1];
    }
    *((T**)&memory[_size - 1]) = nullptr;
}


template <class T>
FastListAllocator<T>::FastListAllocator(size_t size) : _size(size) {
    _init();
}

template <class T>
FastListAllocator<T>::FastListAllocator() : _size(_min_size) {
    _init();

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
    T* next = *((T**)_head);

    T* retVal = _head;
    _head = next;
    return retVal;
}


template <class T>
bool FastListAllocator<T>::free(T *addr) {
    *((T**)addr) = _head;
    _head = addr;
    _loading--;
}


//  ====================================================

template <class T> class Node {
public:
    Node() {};
    Node<T> *_next;
    Node<T> *_prev;
    T value;
};




template <class T> class FastList {
public:
    FastList(size_t size = MIN_SIZE) : allocator(size + 2) {
        _head = allocator._new();
        _tail = allocator._new();

        _head->_next = _tail;
        _head->_prev = nullptr;
        _tail->_prev = _head;
        _tail->_next = nullptr;
    };
    ~FastList() {};

    void traverseAll(std::function<bool(T &)> handler);
    bool push(T val);
    bool remove(Node<T> *node);

private:
    FastListAllocator<Node<T>> allocator;
    Node<T> *_head = nullptr;
    Node<T> *_tail = nullptr;
};


template <class T>
void FastList<T>::traverseAll(std::function<bool(T &)> handler) {
    Node<T> *current = _head;
    while(current != nullptr) {
        if (!handler(current->value)) {
            current = current->_next;
            remove(current->_prev);
        } else {
            current = current->_next;
        }
    }
    std::cout << std::endl;
}



template <class T>
bool FastList<T>::push(T val) {
    auto nxt = allocator._new();
    if (!nxt) {
        return false;
    }
    nxt->value = val;
    _tail->_next = nxt;
    _tail->_next->_prev = _tail;
    _tail->_next->_next = nullptr;
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
