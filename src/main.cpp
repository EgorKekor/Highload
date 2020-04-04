#include <iostream>

#include "../include/server.h"
#include <iostream>

int main() {
    Server server(ADDRESS, PORT, MAX_EPOLL_EVENT);
    server.Listen();
    return 0;
}