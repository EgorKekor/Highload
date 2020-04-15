//
// Created by kekos on 06.04.2020.
//

#ifndef HIGHLOAD_CONVEYORPART_HPP
#define HIGHLOAD_CONVEYORPART_HPP

#include <iostream>
#include <functional>
#include <thread>
#include "defines.h"

template <class INP_CONTAINER, class OUT_CONTAINER>
class ConveyorPart {
public:
    ConveyorPart(
            std::shared_ptr<INP_CONTAINER> &input,
            std::shared_ptr<OUT_CONTAINER> &output) :
    input(input),
    output(output) {};

    std::shared_ptr<INP_CONTAINER> &input;
    std::shared_ptr<OUT_CONTAINER> &output;
};



#endif //HIGHLOAD_CONVEYORPART_HPP
