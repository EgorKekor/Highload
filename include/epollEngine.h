//
// Created by kekor on 26.03.20.
//

#ifndef HIGHLOAD_EPOLLENGINE_H
#define HIGHLOAD_EPOLLENGINE_H

#include <atomic>
#include <sys/epoll.h>
#include "../include/config.h"

class Epoll {
private:
    int epollfd;
    int maxEpollEvents;
    int timeout;

public:
    Epoll(int maxEpollEvents, int timeout);
    ~Epoll();

    Epoll(const Epoll&) = default;

    int AddFd(int clientfd, int epollfd);
    int AddFd(int clientfd, int epollfd, void* ptr);

    void deleteFd(int fd);

    int AddPollFd(int clientfd, int epollfd);
    ssize_t Wait(epoll_event* events);
    int Epollfd();
};

#endif //HIGHLOAD_EPOLLENGINE_H
