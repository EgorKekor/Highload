//
// Created by kekos on 05.04.2020.
//

#ifndef HIGHLOAD_POINTERSTRINGSTREAM_H
#define HIGHLOAD_POINTERSTRINGSTREAM_H

#include <iostream>
#include <memory>
#include <boost/utility/string_ref.hpp>

class PointerStringStream {
public:
    PointerStringStream(std::string *str);
    char getChar();
    boost::string_ref getWord();
    boost::string_ref getLine();

private:
    void _eat();
    std::string *_str = nullptr;
    size_t _head = 0;
};

#endif //HIGHLOAD_POINTERSTRINGSTREAM_H
