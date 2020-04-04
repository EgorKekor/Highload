//
// Created by kekos on 03.04.2020.
//

#ifndef HIGHLOAD_STRINGHOLDER_H
#define HIGHLOAD_STRINGHOLDER_H

#include <iostream>
#include <map>
#include <string>
#include "../include/fastList.h"
#include "../include/config.h"

class StringHolder {
public:
    StringHolder(size_t stringsAmount = MAX_CONNECTIONS);
    ~StringHolder();
    bool append(SOCKET key, char *buf);

    void endOfData(SOCKET sock);
private:
    FastList<std::string*> _reservedPool;
    std::map<SOCKET, std::string &> _messages;
};

#endif //HIGHLOAD_STRINGHOLDER_H
