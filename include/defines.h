//
// Created by kekos on 06.04.2020.
//

#ifndef HIGHLOAD_DEFINES_H
#define HIGHLOAD_DEFINES_H

#include <iostream>
#include <vector>

#define SOCKET    int

#define CONVEYOR_PART_UNIQUE std::unique_ptr<ConveyorPart<INP_CONT, OUT_CONT>>
#define CONVEYOR_PART = ConveyorPart<INP_CONT, OUT_CONT>;

#define CONVEYOR_0_INPUT  SOCKET
#define CONVEYOR_0_OUTPUT   std::unique_ptr<Request>

#define CONVEYOR_1_INPUT  CONVEYOR_0_OUTPUT
#define CONVEYOR_1_OUTPUT   std::pair<SOCKET, std::unique_ptr<Request>>

namespace http {
    inline std::vector<std::string> methods {
            std::string("HEAD"),
            std::string("GET"),
    };
}

#endif //HIGHLOAD_DEFINES_H
