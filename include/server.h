//
// Created by kekor on 26.03.20.
//

#ifndef HIGHLOAD_SERVER_H
#define HIGHLOAD_SERVER_H

#include <iostream>
#include "../include/config.h"
#include "../include/epollEngine.h"
#include "../include/reader.h"


class Server {
private:
    int masterSocket;
    bool stop;
    Epoll *epollEngine;
    Reader *reader;
    bool _setNonBlock(int fd);
public:
    Server(const std::string &addr, const std::uint16_t &port, const std::uint32_t &queueSize);
    ~Server();

    void Listen();
};

#endif //HIGHLOAD_SERVER_H
