//
// Created by kekos on 06.04.2020.
//

#ifndef HIGHLOAD_SIMPLECONVEYORPART_HPP
#define HIGHLOAD_SIMPLECONVEYORPART_HPP

#include <iostream>
#include <functional>
#include <thread>
#include "defines.h"

template <class INP_CONTAINER, class OUT_CONTAINER>
class SimpleConveyorPart {
public:
    typedef SimpleConveyorPart<INP_CONTAINER, OUT_CONTAINER> this_type;

    SimpleConveyorPart(const this_type &rh) : input(rh.input), output(rh.output) {
        std::cout << "COPY111!" << std::endl;
    };

    SimpleConveyorPart(this_type &&rh) : input(rh.input), output(rh.output) {
        std::cout << "MOVE111!" << std::endl;
    };

    SimpleConveyorPart(
            std::shared_ptr<INP_CONTAINER> &input,
            std::shared_ptr<OUT_CONTAINER> &output) :
    input(input),
    output(output) {};

    std::shared_ptr<INP_CONTAINER> &input;
    std::shared_ptr<OUT_CONTAINER> &output;
};



#endif //HIGHLOAD_SIMPLECONVEYORPART_HPP
