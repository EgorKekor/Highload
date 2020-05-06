//
// Created by kekor on 26.03.20.
//

#include "../include/server.h"
#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <iostream>
#include <cstring>
#include <unistd.h>


Server::Server(const std::string &addr,
        const std::uint16_t &port,
        const std::uint32_t &queueSize,
        std::shared_ptr<BlockQueue<CONVEYOR_0_INPUT>> output) : stop(false), output(output) {

    epollEngine = new Epoll(MAX_EPOLL_EVENT, EPOLL_TIMEOUT);
    //reader = new Reader;

    masterSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (masterSocket < 0) {
        throw std::runtime_error("exception socket create" + std::string(strerror(errno)));
    }
    int reuse = 1;
    setsockopt(masterSocket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, (const char*)&reuse, sizeof(reuse));

    int flags = fcntl(masterSocket, F_GETFL, 0);
    if (fcntl(masterSocket, F_SETFL, flags | O_NONBLOCK) == -1) {
        throw std::runtime_error("nonblocked: " + std::string(strerror(errno)));
    }


    sockaddr_in serveraddr;
    serveraddr.sin_family = AF_INET;
    inet_pton(AF_INET, addr.data(), &(serveraddr.sin_addr));
    serveraddr.sin_port = htons(port);

    if (bind(masterSocket, (struct sockaddr *) &serveraddr, sizeof(serveraddr)) < 0) {
        throw std::runtime_error("bind: " + std::string(strerror(errno)));
    }


    if (listen(masterSocket, queueSize) < 0) {
        throw std::runtime_error("listen: " + std::string(strerror(errno)));
    }

    epollEngine->AddFd(masterSocket, epollEngine->Epollfd());
}

Server::~Server() {
    delete epollEngine;
    close(masterSocket);
}


void Server::Listen() {
    sockaddr_in clientaddr;
    socklen_t clientlen;

    epoll_event events[MAX_EPOLL_EVENT];

    while (!stop) {
        ssize_t fdCount = epollEngine->Wait(events);
        for (uint32_t i = 0; i < fdCount; ++i) {
//            if (events[i].events & EPOLLERR) {
//                std::cout << "server.cpp: client socket EPOLLERR" << std::endl;
////                close(events[i].data.fd);
//            } else if (events[i].events & EPOLLHUP) {
//                std::cout << "server.cpp: client socket EPOLLHUP" << std::endl;
////                close(events[i].data.fd);
//            } else if (events[i].events & EPOLLRDHUP) {
//                std::cout << "server.cppz: client socket EPOLLRDHUP:" << events[i].data.fd << std::endl;
////                close(events[i].data.fd);
//            } else
                if (events[i].data.fd == masterSocket) {
                for (;;) {
                    ssize_t conectionFd = accept(masterSocket, (sockaddr *) &clientaddr, &clientlen);
                    if ((conectionFd >= 0) && (_setNonBlock((int) conectionFd))) {
                        epollEngine->AddFd((int)conectionFd, epollEngine->Epollfd());
                    } else {
                        if (errno == EAGAIN || errno == EWOULDBLOCK) {
                            break;
                        } else {
                            std::cerr << "accept: " + std::string(strerror(errno)) << std::endl;
//                            throw std::runtime_error("accept: " + std::string(strerror(errno)));
                        }
                    }
                }
            } else {
                output->push(events[i].data.fd);
            }
        }
    }
}


bool Server::_setNonBlock(int fd) {
    int flags = fcntl(fd, F_GETFL, 0);

    if (fcntl(fd, F_SETFL, flags | O_NONBLOCK) == -1) {
        return false;
    }
    return true;
}




















