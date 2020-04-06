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
#include "../include/pointerStringStream.h"
#include "../include/httpParser.h"


class StringHolder {
public:
    StringHolder(size_t stringsAmount = MAX_CONNECTIONS);
    ~StringHolder();
    bool append(SOCKET key, char *buf);

    void endOfData(SOCKET sock);
private:
    HttpParser _httpParser;
    FastList<std::string*> _reservedPool;
    std::map<SOCKET, std::string &> _messages;
};

#endif //HIGHLOAD_STRINGHOLDER_H
