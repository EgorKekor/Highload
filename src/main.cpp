#include <iostream>

#include "../include/server.h"
#include <iostream>
#include <sstream>
#include <memory>
#include <queue>
#include "../include/conveyorPart.hpp"


int main() {
    auto q1 = std::make_shared<BlockQueue<std::string>>();
    auto q2 = std::make_shared<BlockQueue<std::string>>();

    q1->push("bebebe");
    q1->push("bababa");

    ConveyorPart<BlockQueue<std::string>, BlockQueue<std::string>> conveyor(
            q1,
            q2,
            [](std::unique_ptr<ConveyorPart<BlockQueue<std::string>, BlockQueue<std::string>>> conveyor) {
                for(;;) {
                    std::cout << conveyor->input->blockPeek() << std::endl;
                    conveyor->input->blockPop();
                }
            });

    sleep(2);
    q1->push("lol");
    sleep(2);
    q1->push("kek");
    sleep(2);

//    Server server(ADDRESS, PORT, MAX_EPOLL_EVENT);
//    server.Listen();
    exit(0);
}