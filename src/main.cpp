
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
#include <sys/wait.h>




Config *config = nullptr;

int main(int argc, char *argv[]) {
    Server server(ADDRESS, PORT, MAX_EPOLL_EVENT);

    for (int i = 0; i < PROC; ++i) {
        pid_t pid = 0;
        int status = 0;
        switch(pid=fork()) {
            case -1:
                std::cerr << "Fork error" << std::endl;
                exit(1);
            case 0: {
                config = new Config();
                boost::filesystem::create_directories(config->rootDir());
                std::cout << config->rootDir() + "file1.txt" << std::endl;

                auto sockets = std::make_shared<BlockQueue<CONVEYOR_10_INPUT>>();
                auto uptr_request = std::make_shared<BlockQueue<CONVEYOR_10_OUTPUT>>();


                Reader<BlockQueue<CONVEYOR_10_INPUT>, BlockQueue<CONVEYOR_10_OUTPUT>> reader(
                        sockets,
                        uptr_request);

                auto responces = std::make_shared<BlockQueue<CONVEYOR_20_OUTPUT>>();
                ResponseMaker<BlockQueue<CONVEYOR_20_INPUT >, BlockQueue<CONVEYOR_20_OUTPUT>> maker(
                        uptr_request,
                        responces);

                auto results = std::make_shared<BlockQueue<CONVEYOR_30_OUTPUT>>();
                Writer<BlockQueue<CONVEYOR_30_INPUT >, BlockQueue<CONVEYOR_30_OUTPUT>> writer(
                        responces,
                        results);

                server.initEpoll();
                server.setOutput(sockets);
                server.Listen();
                exit(0);
            }
            default:
                if (i == PROC - 1) {
                    wait(&status);
                }
        }
    }





    exit(0);
}