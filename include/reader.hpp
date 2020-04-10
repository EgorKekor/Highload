//
// Created by kekos on 07.04.2020.
//

#ifndef HIGHLOAD_READER_HPP
#define HIGHLOAD_READER_HPP

#include <iostream>
#include <sys/socket.h>
#include <unistd.h>
#include <thread>
#include "../include/config.h"
#include "../include/conveyorPart.hpp"
#include "../include/fastList.hpp"
#include "stringHolder.h"

template <class INP_CONT, class OUT_CONT>
class Reader : public ConveyorPart<INP_CONT, OUT_CONT> {
public:
    typedef CONVEYOR_0_INPUT reader_input;
    typedef CONVEYOR_0_OUTPUT uptr_reader_output;
    typedef std::unique_ptr<Reader<INP_CONT, OUT_CONT>> this_unique;
    typedef Reader<INP_CONT, OUT_CONT> this_type;

    Reader(std::shared_ptr<INP_CONT> input,
           std::shared_ptr<OUT_CONT> output) :
            ConveyorPart<INP_CONT, OUT_CONT>(
                    input, output),
                    _stringHolder(
                            output,
                            STRINGS_AMOUNT) {
        std::thread workerThr(_readWorker, this_unique(this));
        workerThr.detach();
    };
private:
    StringHolder _stringHolder;
    static void _readWorker(this_unique thisPart);
};

template<class INP_CONT, class OUT_CONT>
void Reader<INP_CONT, OUT_CONT>::_readWorker(this_unique thisPart) {
    for (;;) {
        char buf[READ_BUF_SIZE];
        reader_input clientSocket = thisPart->input->blockPeek();

        for (;;) {
            //std::cout << "=============" << std::endl;
            ssize_t nbytes = recv(clientSocket, buf, sizeof(buf), 0);

            if (nbytes == -1) {
                thisPart->_stringHolder.append(clientSocket, nullptr);
                if (errno == EAGAIN || errno == EWOULDBLOCK) {
                    std::cout << "[" << clientSocket << "]:" << "EWOULDBLOCK" << std::endl;
                    break;
                } else {
                    std::cerr << "[" << clientSocket << "]:" << "Read error" << std::endl;
                    break;
                }
            } else if (nbytes == 0) {
                thisPart->_stringHolder.append(clientSocket, nullptr);
                close(clientSocket);
                std::cout << "[" << clientSocket << "]:" << "closed" << std::endl;
                break;
            } else {
                if (READ_BUF_SIZE != nbytes) {
                    buf[nbytes] = '\0';
                }
                thisPart->_stringHolder.append(clientSocket, buf);
            }
        }
        thisPart->input->blockPop();
//break;
    }
}


#endif //HIGHLOAD_READER_HPP
