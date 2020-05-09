//
// Created by kekor on 26.03.20.
//

#ifndef HIGHLOAD_SERVER_H
#define HIGHLOAD_SERVER_H

#include <iostream>
#include <sys/socket.h>
#include <unistd.h>
#include <thread>
#include "../include/config.h"
#include "../include/epollEngine.h"
#include "../include/blockQueue.hpp"
#include "../include/defines.h"
//#include "../include/reader.h"


class Server {
private:
    int masterSocket;
    bool stop;
    Epoll *epollEngine;
    std::shared_ptr<BlockQueue<CONVEYOR_10_INPUT>> output;
    bool _setNonBlock(int fd);
public:
    Server(
            const std::string &addr,
            const std::uint16_t &port,
            const std::uint32_t &queueSize);
    ~Server();

    void initEpoll();
    void setOutput(std::shared_ptr<BlockQueue<CONVEYOR_10_INPUT>> &out);
    void Listen();
};

#endif //HIGHLOAD_SERVER_H
