//
// Created by kekos on 05.04.2020.
//

#ifndef HIGHLOAD_RETURNS_H
#define HIGHLOAD_RETURNS_H

#include <iostream>
#include <functional>
#include <utility>

class StringHolderReturn {
public:
    StringHolderReturn(std::function<bool()> handler, std::string* str) : _str(str), _handler(std::move(handler)) {};
    ~StringHolderReturn() {
        _handler();
        _str = nullptr;
    };
    std::string *get() {return _str;};
private:
    std::string *_str;
    std::function<bool()> _handler;
};

#endif //HIGHLOAD_RETURNS_H
