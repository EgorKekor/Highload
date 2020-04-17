//
// Created by kekos on 15.04.2020.
//

#ifndef HIGHLOAD_REQUESTHANDLER_HPP
#define HIGHLOAD_REQUESTHANDLER_HPP

#include <iostream>
#include <sys/socket.h>
#include <unistd.h>
#include <thread>
#include <vector>
#include "../include/config.h"
#include "../include/defines.h"
#include "../include/request.h"
#include "simpleConveyorPart.hpp"
#include "spreadConveyorPart.hpp"


template <class INP_CONTAINER, class OUT_CONTAINER>
class RequestHandler : public SimpleConveyorPart<INP_CONTAINER, OUT_CONTAINER> {
public:
    typedef CONVEYOR_100_INPUT this_input;
    typedef CONVEYOR_100_OUTPUT this_output;
    typedef std::unique_ptr<RequestHandler<INP_CONTAINER, OUT_CONTAINER>> this_unique;
    typedef RequestHandler<INP_CONTAINER, OUT_CONTAINER> this_type;

    ~RequestHandler() {
        std::cout << "RequestHandler destroyed" << std::endl;
    };


    RequestHandler(
            std::shared_ptr<INP_CONTAINER> &input,
            std::shared_ptr<OUT_CONTAINER> &output) :
            SimpleConveyorPart<INP_CONTAINER, OUT_CONTAINER>(input, output) {
        count++;
        std::thread workerThr(_readWorker, this_unique(this));
        workerThr.detach();
    };

private:
    static std::atomic_int count;
    static void _readWorker(this_unique thisPart);
};

template<class INP_CONTAINER, class OUT_CONTAINER>
std::atomic_int RequestHandler<INP_CONTAINER, OUT_CONTAINER>::count = 0;

template<class INP_CONTAINER, class OUT_CONTAINER>
void RequestHandler<INP_CONTAINER, OUT_CONTAINER>::_readWorker(RequestHandler::this_unique thisPart) {
    int myNum = thisPart->count;
    std::cout << myNum << std::endl;
    sleep(50);
}

#endif //HIGHLOAD_REQUESTHANDLER_HPP
