//
// Created by kekor on 27.03.20.
//

#ifndef HIGHLOAD_LISTALLOCATOR_H
#define HIGHLOAD_LISTALLOCATOR_H

#include <cstddef>
#include <functional>
#include <cstring>
#include "../include/config.h"


template <class T> class FastListAllocator {
public:
    typedef int*    pointer;

    FastListAllocator();
    FastListAllocator(size_t size);
    ~FastListAllocator();

    T* _new();
    void free(T *node);

private:
    T *memory;
    T* _head = nullptr;
    size_t _capacity;
    size_t _loading = 0;
    const size_t _min_size = MIN_SIZE;

    void _init();
};

template <class T>
void FastListAllocator<T>::_init() {
    if (sizeof(T) < sizeof(pointer)) {
        throw std::runtime_error("FastListAllocator constructor: Wrong data type");
    }
    memory = new T[_capacity];
    _head = memory;
    for (size_t i = 0; i < _capacity - 1; ++i) {
        *((T**)(&memory[i])) = &memory[i + 1];
    }
    *((T**)&memory[_capacity - 1]) = nullptr;
}


template <class T>
FastListAllocator<T>::FastListAllocator(size_t size) : _capacity(size) {
    _init();
}

template <class T>
FastListAllocator<T>::FastListAllocator() : _capacity(_min_size) {
    _init();

}

template <class T>
FastListAllocator<T>::~FastListAllocator() {
    delete [] memory;
}



template <class T>
T* FastListAllocator<T>::_new() {
    if (_loading == _capacity) {
        return nullptr;
    }

    _loading++;
    T* next = *((T**)_head);

    T* retVal = _head;
    _head = next;
    return retVal;
}


template <class T>
void FastListAllocator<T>::free(T *addr) {
    *((T**)addr) = _head;
    _head = addr;
    _loading--;
}


//  ====================================================

template <class T> class Node {
public:
    Node() {};
    T value;
    Node<T> *_next;
    Node<T> *_prev;
};


template <class T> class FastList {
public:
    FastList(size_t size = MIN_SIZE) : allocator(size + 2), _capasity(size) {
        _head = allocator._new();
        _tail = allocator._new();

        _head->_next = _tail;
        _head->_prev = nullptr;
        _tail->_prev = _head;
        _tail->_next = nullptr;
    };
    ~FastList() {};

    void traverseAll(std::function<bool(T &)> handler);
    bool push(T &val);
    bool push(T &&val);
    bool remove(Node<T> *node);


    T& peekFront();
    void popFront();
    size_t size(){ return _size;};
private:
    size_t _size = 0;
    size_t _capasity= 0;
    FastListAllocator<Node<T>> allocator;
    Node<T> *_head = nullptr;
    Node<T> *_tail = nullptr;
};


template <class T>
void FastList<T>::traverseAll(std::function<bool(T &)> handler) {
    Node<T> *current = _head->_next;
    while(current != _tail) {
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
bool FastList<T>::push(T &val) {
    auto newNode = allocator._new();
    if (!newNode) {
        return false;
    }
    new(&newNode->value) T(val);
    //newNode->value = val;
    newNode->_next = _tail;
    newNode->_prev = _tail->_prev;
    _tail->_prev->_next = newNode;
    _tail->_prev = newNode;

    _size++;
    return true;
}

template <class T>
bool FastList<T>::push(T &&val) {
    auto newNode = allocator._new();
    if (!newNode) {
        return false;
    }
    //newNode->value = std::move(val);
    new(&newNode->value) T(std::move(val));
    newNode->_next = _tail;
    newNode->_prev = _tail->_prev;
    _tail->_prev->_next = newNode;
    _tail->_prev = newNode;

    _size++;
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
    _size--;
    return true;
}

template<class T>
T& FastList<T>::peekFront() {
    Node<T>* ret = _head->_next;
    T *val = &(ret->value);
    return *val;
}

template<class T>
void FastList<T>::popFront() {
    Node<T>* ret = _head->_next;
    remove(ret);
}


// =======================================
// =======================================


template<class T>
class FastListReturner {
public:
    FastListReturner(FastList<T> *fl) : _fastList(fl) {};
    FastListReturner(T& val, FastList<T> *fl) : _value(val), _fastList(fl), _isRvalue(false) {};
    FastListReturner(T&& val, FastList<T> *fl) : _value(std::move(val)), _fastList(fl), _isRvalue(true) {};

    T& get() { return _value; };

    ~FastListReturner() {
        if (_fastList == nullptr) {
            return;
        }
        if (_isRvalue) {
            std::cout << "rvalue returned" << std::endl;
            std::cout << "size before: " << _fastList->size() << std::endl;
            _fastList->push(std::move(_value));
            std::cout << "size after: " << _fastList->size() << std::endl;
        }
    };
private:
    bool _isRvalue;
    T _value;
    FastList<T> *_fastList;
};


#endif //HIGHLOAD_LISTALLOCATOR_H
