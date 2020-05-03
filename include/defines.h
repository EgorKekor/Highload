//
// Created by kekos on 06.04.2020.
//

#ifndef HIGHLOAD_DEFINES_H
#define HIGHLOAD_DEFINES_H

#include <iostream>
#include <vector>
#include <memory>

#define SOCKET    int

#define CONVEYOR_PART_UNIQUE std::unique_ptr<ConveyorPart<INP_CONT, OUT_CONT>>
#define CONVEYOR_PART = ConveyorPart<INP_CONT, OUT_CONT>;

#define CONVEYOR_0_INPUT  SOCKET
#define CONVEYOR_0_OUTPUT   std::unique_ptr<Request>

#define CONVEYOR_10_INPUT  CONVEYOR_0_OUTPUT
#define CONVEYOR_10_OUTPUT   std::unique_ptr<Response>

#define CONVEYOR_20_INPUT  CONVEYOR_10_OUTPUT
#define CONVEYOR_20_OUTPUT   std::pair<SOCKET, bool>

namespace http {
    inline std::vector<std::string> methods {
            std::string("HEAD"),
            std::string("GET"),
    };
}

inline void my_free(void* p) {
    free(p);
}

template<class T>
using unique_ptr_free = std::unique_ptr<T, decltype(&my_free)>;

template<class T>
inline std::unique_ptr<T, decltype(&my_free)> make_unique_free(T* ptr) {
    return std::unique_ptr<T, decltype(&my_free)>(ptr, &my_free);
}


#endif //HIGHLOAD_DEFINES_H
