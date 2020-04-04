//
// Created by kekos on 03.04.2020.
//

#include "../include/stringHolder.h"


StringHolder::StringHolder(size_t stringsAmount) : _reservedPool(stringsAmount) {
    std::string str1("aa");
    std::string str2;
    str2 = str1;
    for (size_t i = 0; i < stringsAmount; ++i) {
        auto *reserveStr = new std::string;
        reserveStr->reserve(AVERAGE_CLIENT_MESSAGE);
        _reservedPool.push(reserveStr);
    }
}

StringHolder::~StringHolder() {

}

bool StringHolder::append(SOCKET key, char *buf) {
    if (_reservedPool.size() == 0) {
        return false;
    }

    if (_messages.find(key) == _messages.end()) {
        std::string *str = _reservedPool.popFront();
        str->append(buf);
        _messages.insert(std::pair<SOCKET, std::string&>(key, *str));
    } else {
        _messages.at(key).append(buf);
    }
    return true;
}

void StringHolder::endOfData(SOCKET sock) {
    auto it = _messages.find(sock);
    if (it != _messages.end()) {

    }
}

