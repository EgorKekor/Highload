//
// Created by kekos on 06.04.2020.
//

#ifndef HIGHLOAD_CONVEYORPART_HPP
#define HIGHLOAD_CONVEYORPART_HPP

#include <iostream>
#include <functional>
#include <thread>
#include "defines.h"

template <class INP_CONT, class OUT_CONT>
class ConveyorPart {
public:
    ConveyorPart(
            std::shared_ptr<INP_CONT> input,
            std::shared_ptr<OUT_CONT> output) :
    input(input),
    output(output) {};

    std::shared_ptr<INP_CONT> input;
    std::shared_ptr<OUT_CONT> output;
};



#endif //HIGHLOAD_CONVEYORPART_HPP
