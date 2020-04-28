#include <iostream>

#include "../include/server.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <memory>
#include <map>
#include <queue>
#include <sstream>
#include "../include/simpleConveyorPart.hpp"
#include "../include/blockQueue.hpp"
#include "../include/blockMap.hpp"
#include "../include/reader.hpp"
#include "../include/responseMaker.hpp"
#include "../include/response.h"


std::string &&getStr() {
    std::string a("any");
    return std::move(a);
}

int main() {

    auto sockets = std::make_shared<BlockQueue<CONVEYOR_0_INPUT>>();
    auto uptr_request = std::make_shared<BlockQueue<CONVEYOR_0_OUTPUT>>();


    Reader<BlockQueue<CONVEYOR_0_INPUT>, BlockQueue<CONVEYOR_0_OUTPUT>> reader (
            sockets,
            uptr_request);


    auto responces = std::make_shared<BlockQueue<CONVEYOR_10_OUTPUT>>();
    ResponseMaker<BlockQueue<CONVEYOR_10_INPUT>, BlockQueue<CONVEYOR_10_OUTPUT>> maker (
            uptr_request,
            responces);




    Server server(ADDRESS, PORT, MAX_EPOLL_EVENT, sockets);
    server.Listen();
    exit(0);
}