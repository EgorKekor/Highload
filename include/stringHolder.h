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
#include "../include/conveyorPart.hpp"
#include "../include/blockQueue.hpp"


class StringHolder {
public:
    typedef CONVEYOR_0_OUTPUT reader_output;
    typedef std::unique_ptr<std::string> fast_list_type;
    typedef BlockQueue<CONVEYOR_0_OUTPUT> reader_output_container;

    StringHolder(std::shared_ptr<reader_output_container> output, size_t stringsAmount = STRINGS_AMOUNT);
    bool append(SOCKET key, char *buf);
private:
    std::shared_ptr<reader_output_container> _output;
    HttpParser _httpParser;
    FastList<fast_list_type> _reservedPool;
    std::map<SOCKET, fast_list_type> _messages;
};

#endif //HIGHLOAD_STRINGHOLDER_H
