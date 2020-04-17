//
// Created by kekos on 03.04.2020.
//

#ifndef HIGHLOAD_STRINGHOLDER_H
#define HIGHLOAD_STRINGHOLDER_H

#include <iostream>
#include <map>
#include <string>
#include "fastList.hpp"
#include "../include/config.h"
#include "../include/defines.h"
#include "../include/pointerStringStream.h"
#include "../include/httpParser.h"
#include "simpleConveyorPart.hpp"
#include "../include/blockQueue.hpp"

template <class INP_CONTAINER, class OUT_CONTAINER>
class Reader;

class StringHolder {
public:
    typedef CONVEYOR_0_OUTPUT reader_output;
    typedef CONVEYOR_0_INPUT reader_input;
    typedef std::unique_ptr<std::string> fast_list_type;
    typedef BlockQueue<CONVEYOR_0_OUTPUT> reader_output_container;
    typedef BlockQueue<CONVEYOR_0_INPUT> reader_input_container;

    StringHolder(
            Reader<reader_input_container, reader_output_container> &reader,
            size_t stringsAmount = STRINGS_AMOUNT);
    bool append(SOCKET key, char *buf);
private:
    Reader<reader_input_container, reader_output_container> &_reader;
    HttpParser _httpParser;
    FastList<fast_list_type> _reservedPool;
    std::map<SOCKET, fast_list_type> _messages;
};

#endif //HIGHLOAD_STRINGHOLDER_H
