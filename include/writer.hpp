//
// Created by kekor on 02.05.2020.
//

#ifndef TEST_STRACE_WRITER_HPP
#define TEST_STRACE_WRITER_HPP

#include "../include/simpleConveyorPart.hpp"
#include "../include/response.h"
#include "../include/epollEngine.h"

template <class INP_CONTAINER, class OUT_CONTAINER>
class Writer : public SimpleConveyorPart<INP_CONTAINER, OUT_CONTAINER> {
public:
    typedef CONVEYOR_20_INPUT writer_input;
    typedef CONVEYOR_20_OUTPUT writer_output;
    typedef std::unique_ptr<Writer<INP_CONTAINER, OUT_CONTAINER>> this_unique;
    typedef Writer<INP_CONTAINER, OUT_CONTAINER> this_type;

    ~Writer() {
        std::cout << "Writer destroyed" << std::endl;
    };
    Writer(
            std::shared_ptr<INP_CONTAINER> &input,
            std::shared_ptr<OUT_CONTAINER> &output) :
            SimpleConveyorPart<INP_CONTAINER, OUT_CONTAINER>(input, output),
            _epollEngine(MAX_EPOLL_EVENT, EPOLL_TIMEOUT) {
        std::thread workerThr(_readWorker, this_unique(this));
        workerThr.detach();
        //std::thread writerThr(_writeWorker, this_unique(this));
        //writerThr.detach();
    };
private:
    Epoll _epollEngine;
    static void _readWorker(this_unique thisPart);
    static void _writeWorker(this_unique thisPart);
};

template<class INP_CONTAINER, class OUT_CONTAINER>
void Writer<INP_CONTAINER, OUT_CONTAINER>::_readWorker(Writer::this_unique thisPart) {
    for(;;) {
        auto response = std::move(thisPart->input->blockPeek());

        std::string &header = response->getHeaders();
        ssize_t nbytes = send(response->socket, header.c_str(), header.length(), 0);
        std::cout << nbytes << "Header Отправлено" << std::endl;

        std::shared_ptr<Body>& body = response->getBody();
        nbytes = send(response->socket, body->getAdress(), body->length(), 0);
        std::cout << nbytes << "Body Отправлено" << std::endl;

        thisPart->input->blockPop();
        //break;
    }
}

template<class INP_CONTAINER, class OUT_CONTAINER>
void Writer<INP_CONTAINER, OUT_CONTAINER>::_writeWorker(Writer::this_unique thisPart) {
    epoll_event events[MAX_EPOLL_EVENT];

    for(;;) {
        ssize_t fdCount = thisPart->_epollEngine.Wait(events);
        for (uint32_t i = 0; i < fdCount; ++i) {
            if ((events[i].events & EPOLLERR) || (events[i].events & EPOLLHUP) || (events[i].events & EPOLLRDHUP)) {
                std::cerr << "Writer.hpp: client socket error" << std::endl;
                thisPart->output->push(writer_output(events[i].data.fd, false));
                close(events[i].data.fd);
                continue;
            } else {
                for (;;) {
                }
            }
        }
        break;////////////////////////////////////////////
    }
}

#endif //TEST_STRACE_WRITER_HPP
