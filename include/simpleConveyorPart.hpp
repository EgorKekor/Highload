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

    SimpleConveyorPart(
            std::shared_ptr<INP_CONTAINER> &input,
            std::shared_ptr<OUT_CONTAINER> &output) :
    input(input),
    output(output) {};

    void tryYield();
    std::shared_ptr<INP_CONTAINER> &input;
    std::shared_ptr<OUT_CONTAINER> &output;
};

template<class INP_CONTAINER, class OUT_CONTAINER>
void SimpleConveyorPart<INP_CONTAINER, OUT_CONTAINER>::tryYield() {
    double prop = (double)(output->size() + 1) / (double)(input->size() + 1);
    while (prop >= YIELD_SIZE_PROPORTION) {
        std::this_thread::yield();
        prop = (double)(output->size() + 1) / (double)(input->size() + 1);
    }
}


#endif //HIGHLOAD_SIMPLECONVEYORPART_HPP
