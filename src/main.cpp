#include <iostream>

#include "../include/server.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <memory>
#include <map>
#include <queue>
#include <fcntl.h>
#include "../include/simpleConveyorPart.hpp"
#include "../include/blockQueue.hpp"
#include "../include/blockMap.hpp"
#include "../include/reader.hpp"
#include "../include/requestHandler.hpp"
#include "../include/spreadConveyorPart.hpp"
#include "../include/fastList.hpp"
#include "../include/request.h"
#include "../include/cache.h"


int main() {

//    int fd = open("../tests/cache/test.dat", O_CREAT);
//    close(fd);

    //int fd = open("test.dat", O_RDONLY);

//    Cache cache;
//    cache.get("a");


//    auto sockets = std::make_shared<BlockQueue<CONVEYOR_0_INPUT>>();
//    auto uptr_request = std::make_shared<BlockQueue<CONVEYOR_0_OUTPUT>>();
//
//
//    Reader<BlockQueue<CONVEYOR_0_INPUT>, BlockQueue<CONVEYOR_0_OUTPUT>> reader (
//            sockets,
//            uptr_request);
//
//
//    std::vector<std::shared_ptr<BlockQueue<CONVEYOR_100_INPUT>>> vector_queue_request;
//    vector_queue_request.push_back(std::make_shared<BlockQueue<CONVEYOR_100_INPUT>>());
//    vector_queue_request.push_back(std::make_shared<BlockQueue<CONVEYOR_100_INPUT>>());
//    vector_queue_request.push_back(std::make_shared<BlockQueue<CONVEYOR_100_INPUT>>());
//    vector_queue_request.push_back(std::make_shared<BlockQueue<CONVEYOR_100_INPUT>>());
//
//
//    MoveSpreadConveyorPart<BlockQueue<CONVEYOR_0_OUTPUT>, BlockQueue<CONVEYOR_100_INPUT>> spreader1 (
//            uptr_request,
//            vector_queue_request);




//    std::vector<std::shared_ptr<RequestHandler<BlockQueue<CONVEYOR_100_INPUT>, BlockQueue<CONVEYOR_100_OUTPUT>>>> bank;
//
//    std::vector<RequestHandler<BlockQueue<CONVEYOR_100_INPUT>, BlockQueue<CONVEYOR_100_OUTPUT>>> bank1;
//    bank1.reserve(20);
//    auto results = std::make_shared<BlockQueue<CONVEYOR_100_OUTPUT>>();
//    for (auto queue : vector_queue_request) {
//        bank1.emplace_back(queue, results);
//    }



//    Server server(ADDRESS, PORT, MAX_EPOLL_EVENT, sockets);
//    server.Listen();
    exit(0);
}