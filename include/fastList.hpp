//
// Created by kekor on 27.03.20.
//

#ifndef HIGHLOAD_LISTALLOCATOR_H
#define HIGHLOAD_LISTALLOCATOR_H

#include <cstddef>
#include <functional>
#include <cstring>
#include <mutex>
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
    _head = &memory[0];
    for (size_t i = 0; i < _capacity - 1; ++i) {
        (memory[i].next_block_adress) = &memory[i + 1];
    }
    memory[_capacity - 1].next_block_adress = nullptr;
}


template <class T>
FastListAllocator<T>::FastListAllocator(size_t size) : _capacity(size + 1) {
    _init();
}

template <class T>
FastListAllocator<T>::FastListAllocator() : _capacity(_min_size + 1) {
    _init();

}

template <class T>
FastListAllocator<T>::~FastListAllocator() {
    std::cerr << "List deleted" << std::endl;
    delete [] memory;
}



template <class T>
T* FastListAllocator<T>::_new() {
    if (_loading == _capacity) {
        std::cout << "DANGER! " << _loading << std::endl;
        return nullptr;
    }

    _loading++;

    if (_head == NULL) {
        std::cout << "head==NULL!" << std::endl;
    }
    if (_head->next_block_adress == NULL) {
        std::cout << "next block==NULL!" << std::endl;
    }

    T* retVal = _head;
    _head = _head->next_block_adress;

    return retVal;

}


template <class T>
void FastListAllocator<T>::free(T *addr) {
    if (addr == NULL) {
        std::cout << "FREE NULL" << std::endl;
        return;
    }
    addr->next_block_adress = _head;
    _head = addr;
    _loading--;
//    if (_loading < 100)
//        std::cout << _loading << std::endl;
}


//  ====================================================

template <class T> struct Node {
public:
    Node<T> *next_block_adress;
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

    bool push(T &val);
    bool push(T &&val);
    bool remove(void *node);

    void* getBack() { return _tail->_prev; };

    T& peekAddress(void* addr);
    void popAddress(void* addr);

    T& peekFront();
    void popFront();
    size_t size(){ return _size;};
private:
    std::mutex _operation;
    size_t _size = 0;
    size_t _capasity= 0;
    FastListAllocator<Node<T>> allocator;
    Node<T> *_head = nullptr;
    Node<T> *_tail = nullptr;
};




template <class T>
bool FastList<T>::push(T &val) {
    _operation.lock();
    auto newNode = allocator._new();
    if (!newNode) {
        return false;
    }
    new(&newNode->value) T(val);
    newNode->_next = _tail;
    newNode->_prev = _tail->_prev;
    _tail->_prev->_next = newNode;
    _tail->_prev = newNode;

    _size++;
    _operation.unlock();
    return true;
}

template <class T>
bool FastList<T>::push(T &&val) {
    _operation.lock();
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
    _operation.unlock();
    return true;
}


template <class T>
bool FastList<T>::remove(void *nd) {
    if (nd == NULL) {
        return false;
    }
    Node<T> *node = static_cast<Node<T>*>(nd);
    if ((node == _head) || (node == _tail)) {
        return false;
    }

    node->_prev->_next = node->_next;
    node->_next->_prev = node->_prev;

    //node->value.~T();

    allocator.free(node);
    _size--;
    return true;
}

template<class T>
T& FastList<T>::peekFront() {
    _operation.lock();
    Node<T>* ret = _head->_next;
    _operation.unlock();
    return ret->value;
}

template<class T>
void FastList<T>::popFront() {
    _operation.lock();
    if (_head->_next != _tail) {
        Node<T> *ret = _head->_next;
        remove(ret);
    }
    _operation.unlock();
}

template<class T>
T &FastList<T>::peekAddress(void *addr) {
    _operation.lock();
    Node<T>* ret = static_cast<Node<T>*>(addr);
    _operation.unlock();
    return ret->value;
}

template<class T>
void FastList<T>::popAddress(void *addr) {
    _operation.lock();
    Node<T>* ret = static_cast<Node<T>*>(addr);
    remove(ret);
    _operation.unlock();
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
//            std::cout << "rvalue returned" << std::endl;
//            std::cout << "size before: " << _fastList->size() << std::endl;
            _fastList->push(std::move(_value));
//            std::cout << "size after: " << _fastList->size() << std::endl;
        }
    };
private:
    bool _isRvalue;
    T _value;
    FastList<T> *_fastList;
};


#endif //HIGHLOAD_LISTALLOCATOR_H
