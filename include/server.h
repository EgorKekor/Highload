//
// Created by kekor on 26.03.20.
//

#ifndef HIGHLOAD_SERVER_H
#define HIGHLOAD_SERVER_H

#include <iostream>

#include "../include/epollEngine.h"

#define MAX_EPOLL_EVENT 2000

class Server {
private:

    int masterSocket;
    bool stop;
    Epoll *epollEngine;

    bool _setNonBlock(int fd);

public:
    Server(const std::string& addr, const std::uint16_t& port, const std::uint32_t& queueSize,
           const std::string& root, size_t threadCount);
    ~Server();

    void Listen();
};

#endif //HIGHLOAD_SERVER_H
