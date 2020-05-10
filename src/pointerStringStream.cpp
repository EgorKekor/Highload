//
// Created by kekos on 05.04.2020.
//

#include "../include/pointerStringStream.h"

PointerStringStream::PointerStringStream(std::string *str) : _str(str) {

}

char PointerStringStream::getChar() {
    if (_head < _str->length()) {
        return (*_str)[_head++];
    }
    return EOF;
}

boost::string_ref PointerStringStream::getWord() {
    if (_head == _str->length()) {
        std::string eof;
        eof.push_back(EOF);
        return boost::string_ref(eof);
    }
    const size_t begin = _head;
    while (_head < _str->length()) {
        char c = (*_str)[_head++];
        if (c == ' ' || c == '\r' || c == '\n') {
            boost::string_ref ret(&(*_str)[begin], _head - begin - 1);
            _eat();
            return ret;
        }
    }
    boost::string_ref ret(&(*_str)[begin], _head - begin - 1);
    _eat();
    return ret;
}

boost::string_ref PointerStringStream::getLine() {
    if (_head == _str->length()) {
        std::string eof;
        eof.push_back(EOF);
        return boost::string_ref(eof);
    }
    const size_t begin = _head;
    while (_head < _str->length()) {
        char c = (*_str)[_head++];
        if ( c == '\r' || c == '\n') {
            boost::string_ref ret(&(*_str)[begin], _head - begin - 1);
            _eat();
            return ret;
        }
    }
    boost::string_ref ret(&(*_str)[begin], _head - begin - 1);
    _eat();
    return ret;
}

void PointerStringStream::_eat() {
    while (_head < _str->length() && ((*_str)[_head] == '\r' || (*_str)[_head] == '\n')) {
        _head++;
    }
}

