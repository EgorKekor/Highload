#include <iostream>

#include "../include/server.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <memory>
#include <map>
#include <queue>
#include "../include/conveyorPart.hpp"
#include "../include/blockQueue.hpp"
#include "../include/blockMap.hpp"
#include "../include/reader.hpp"
#include "../include/fastList.hpp"
#include "../include/request.h"


int main() {
//    auto ptr = std::make_shared<std::string>("fff");
//
//    FastList<std::shared_ptr<std::string>> myList;
//    myList.push(std::move(ptr));
//
//    myList.peekFront()->append("ss");
//    myList.popFront();
//
//    //myList.peekFront()->append("ssss");
//    ptr = std::move(myList.peekFront());
//    std::cout << *ptr;



    auto sockets = std::make_shared<BlockQueue<CONVEYOR_0_INPUT>>();
    auto socket_charPtr = std::make_shared<BlockQueue<CONVEYOR_0_OUTPUT>>();

    std::cout << sockets.use_count() << std::endl;

    Reader<BlockQueue<CONVEYOR_0_INPUT>, BlockQueue<CONVEYOR_0_OUTPUT>> reader (
            sockets,
            socket_charPtr);

    std::cout << sockets.use_count() << std::endl;




    Server server(ADDRESS, PORT, MAX_EPOLL_EVENT, sockets);
    server.Listen();
    exit(0);
}