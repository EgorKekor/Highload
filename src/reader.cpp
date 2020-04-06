//
// Created by kekor on 27.03.20.
//

#include "../include/reader.h"
#include <iostream>
#include <sys/socket.h>
#include <unistd.h>
#include <thread>



bool Reader::start() {
    if (_started) {
        return false;
    }
    std::thread readThr(Reader::_readLoop, std::unique_ptr<Reader>(this));
    readThr.detach();
    _started = true;
    return true;
}

void Reader::_readLoop(std::unique_ptr<Reader> inst) {
    for(;;) {
        inst->block();
        std::cout << "unblock" << std::endl;
        auto it = inst->_socketPool.beginIter();

        char buf[READ_BUF_SIZE];
        while(it != inst->_socketPool.tail()) {
            int clientSocket = it->value;

            for(;;) {
                ssize_t nbytes = recv(clientSocket, buf, sizeof(buf), 0);

                if (nbytes == -1) {
                    inst->_holder.endOfData(clientSocket);
                    if (errno == EAGAIN || errno == EWOULDBLOCK) {
                        std::cout << "[" << clientSocket << "]:" << "EWOULDBLOCK" << std::endl;
                        break;
                    } else {
                        std::cerr << "[" << clientSocket << "]:" << "Read error" << std::endl;
                        break;
                    }
                } else if (nbytes == 0) {
                    inst->_holder.endOfData(clientSocket);
                    close(clientSocket);
                    std::cout << "[" << clientSocket << "]:" << "closed" << std::endl;
                    break;
                } else {
                    if (READ_BUF_SIZE != nbytes) {
                        buf[nbytes] = '\0';
                    }
                    inst->_holder.append(clientSocket, buf);
                    std::cout << "[" << clientSocket << "]:" << "Readed: " << nbytes << std::endl;
                }
            }

            it = it->_next;
            inst->_socketPool.remove(it->_prev);
        }
//break;
    }
}

bool Reader::push(SOCKET val) {
    if (_socketPool.push(val)) {
        if (_blocked) {
            _haveData.notify_all();
        }
        return true;
    }
    return false;
}

void Reader::block() {
    _blocked = true;
    _haveDataMutex.lock();
    _haveData.wait(_haveDataMutex);
    _blocked = false;
    _haveDataMutex.unlock();
}
