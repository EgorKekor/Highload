//
// Created by kekos on 02.04.2020.
//

#ifndef HIGHLOAD_CONFIG_H
#define HIGHLOAD_CONFIG_H

#include <string>

#define MB  1048576
#define GB  1073741824

#define MAX_EPOLL_EVENT 10000
#define EPOLL_TIMEOUT -1
#define MAX_CONNECTIONS 10000
#define READ_BUF_SIZE   10

// Writer
#define WRITE_SIZE  64

#define ADDRESS  "127.0.0.1"
#define PORT  8080

// FastList
#define MIN_SIZE    MAX_CONNECTIONS

// StringHolder
#define AVERAGE_CLIENT_MESSAGE  1024
#define STRINGS_AMOUNT  MAX_CONNECTIONS

// Convayor
#define BASE_RESERVE_SIZE   1024

// Cache
#define MAX_CACHE_SIZE  100 * MB
#define RATE_INTERVAL  std::chrono::seconds{1}


// AsyncReader
#define IOCB_SIZE   128
#define MAX_FILES_BLOCK   8

#define ROOT_DIR    "/home/kekor/Highload/root/"


class Config {
public:
    Config();

    const size_t getAlign();
    const std::string& rootDir();
private:
    const std::string _rootDir;
};


#endif //HIGHLOAD_CONFIG_H
