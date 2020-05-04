
#include "../include/server.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <memory>
#include <map>
#include <queue>
#include <sstream>
#include <fcntl.h>
#include "../include/simpleConveyorPart.hpp"
#include "../include/blockQueue.hpp"
#include "../include/blockMap.hpp"
#include "../include/reader.hpp"
#include "../include/responseMaker.hpp"
#include "../include/response.h"
#include "../include/writer.hpp"
#include <boost/filesystem.hpp>
#include <sys/ioctl.h>



Config *config = nullptr;

class Test {
public:
    Test() {
        std::cout << "Constructor called" << std::endl;
    };
    ~Test() {
        std::cout << "Destructor called" << std::endl;
    }
};

int main(int argc, char *argv[]) {
    config = new Config();
    boost::filesystem::create_directories(config->rootDir());


    std::cout << config->rootDir() + "file1.txt" << std::endl;

    auto sockets = std::make_shared<BlockQueue<CONVEYOR_0_INPUT>>();
    auto uptr_request = std::make_shared<BlockQueue<CONVEYOR_0_OUTPUT>>();


    Reader<BlockQueue<CONVEYOR_0_INPUT>, BlockQueue<CONVEYOR_0_OUTPUT>> reader (
            sockets,
            uptr_request);

    auto responces = std::make_shared<BlockQueue<CONVEYOR_10_OUTPUT>>();
    ResponseMaker<BlockQueue<CONVEYOR_10_INPUT>, BlockQueue<CONVEYOR_10_OUTPUT>> maker (
            uptr_request,
            responces);

    auto results = std::make_shared<BlockQueue<CONVEYOR_20_OUTPUT>>();
    Writer<BlockQueue<CONVEYOR_20_INPUT>, BlockQueue<CONVEYOR_20_OUTPUT>> writer (
            responces,
            results);


    Server server(ADDRESS, PORT, MAX_EPOLL_EVENT, sockets);
    server.Listen();
    exit(0);
}