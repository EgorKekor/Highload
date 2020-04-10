//
// Created by kekos on 02.04.2020.
//

#ifndef HIGHLOAD_CONFIG_H
#define HIGHLOAD_CONFIG_H

#define MAX_EPOLL_EVENT 2000
#define EPOLL_TIMEOUT -1
#define MAX_CONNECTIONS 10000
#define READ_BUF_SIZE   10

#define ADDRESS  "127.0.0.1"
#define PORT  8080

// FastList
#define MIN_SIZE    MAX_CONNECTIONS

// StringHolder
#define AVERAGE_CLIENT_MESSAGE  1024
#define STRINGS_AMOUNT  MAX_CONNECTIONS

// Convayor
#define BASE_RESERVE_SIZE   1024


#endif //HIGHLOAD_CONFIG_H
