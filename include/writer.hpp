//
// Created by kekor on 02.05.2020.
//

#ifndef TEST_STRACE_WRITER_HPP
#define TEST_STRACE_WRITER_HPP

#include "../include/simpleConveyorPart.hpp"
#include "../include/response.h"
#include "../include/epollEngine.h"
#include "../include/blockMap.hpp"
#include <signal.h>


void sigpipe_handler(int unused) {
    std::cout << "SIGPIPE!!!!!!!!!!" << std::endl;
    return;
}


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
        std::thread writerThr(_writeWorker, this_unique(this));
        writerThr.detach();
    };
private:
    FastList<CONVEYOR_10_OUTPUT> _processList;
    std::map<SOCKET, CONVEYOR_10_OUTPUT> _processMap;
    Epoll _epollEngine;
    static void _readWorker(this_unique thisPart);
    static void _writeWorker(this_unique thisPart);
    std::mutex _operation;
    static bool _setNonBlock(int fd);
    void _def(Writer::this_unique &thisPart, int socket, void *ptr);
};

template<class INP_CONTAINER, class OUT_CONTAINER>
void Writer<INP_CONTAINER, OUT_CONTAINER>::_readWorker(Writer::this_unique thisPart) {
    struct sigaction sig{SIG_IGN};
    sigaction(SIGPIPE, &sig, NULL);
    for(;;) {
        auto response = std::move(thisPart->input->blockPeek());
        thisPart->input->blockPop();
        int fd = response->socket;
//
//        int epollFd = thisPart->_epollEngine.Epollfd();
//        if (response == nullptr) {
//            exit(0);
//        }
//        thisPart->_operation.lock();
//        thisPart->_processMap.insert(std::pair<SOCKET, CONVEYOR_10_OUTPUT>(fd, std::move(response)));
//        thisPart->_operation.unlock();
//        thisPart->_epollEngine.AddPollFd(fd, epollFd);





        int epollFd = thisPart->_epollEngine.Epollfd();

        thisPart->_processList.push(std::move(response));

        void* respAddr = thisPart->_processList.getBack();

        if (_setNonBlock((int)fd)) {
            thisPart->_epollEngine.AddFd(fd, epollFd, respAddr);
        } else {
            std::cerr << "Writer.hpp: can't set non block mode" << std::endl;
        }



//        std::string &header = response->getHeaders();
//        ssize_t nbytes = send(response->socket, header.c_str(), header.length(), 0);
//
//        std::shared_ptr<Body>& body = response->getBody();
//        nbytes = send(response->socket, body->getAdress(), body->length(), 0);
//
//        thisPart->output->push(writer_output(fd, false));
//        shutdown(fd, 2);
    }
}

template<class INP_CONTAINER, class OUT_CONTAINER>
void Writer<INP_CONTAINER, OUT_CONTAINER>::_writeWorker(Writer::this_unique thisPart) {
    epoll_event events[MAX_EPOLL_EVENT];

    for(;;) {
        ssize_t fdCount = thisPart->_epollEngine.Wait(events);
        for (uint32_t i = 0; i < fdCount; ++i) {
            std::unique_ptr<Response>& response = thisPart->_processList.peekAddress(events[i].data.ptr);
            if (response.get() == nullptr) {
                std::cout << "Miss--" << events[i].data.ptr << std::endl;
                continue;
            }
            int socket = response->socket;

            if (events[i].events & EPOLLERR) {
//                std::cerr << "Writer.hpp: client socket EPOLLERR" << std::endl;
                thisPart->_def(thisPart, socket, events[i].data.ptr);
            } else if (events[i].events & EPOLLHUP) {
//                std::cerr << "Writer.hpp: client socket EPOLLHUP" << std::endl;
                thisPart->_def(thisPart, socket, events[i].data.ptr);
            } else if (events[i].events & EPOLLRDHUP) {
//                std::cerr << "Writer.hpp: client socket EPOLLRDHUP" << std::endl;
                thisPart->_def(thisPart, socket, events[i].data.ptr);
            } else if (!response->headersWriteDone()) {
                const char* buf = response->getAdress();
                    size_t nbytes = send(socket, buf, response->length() - response->justHeadSent(), 0);
                    if (nbytes == -1) {
                        if (errno == EAGAIN || errno == EWOULDBLOCK) {
                            continue;
                        } else {
                            std::cerr << "[" << socket << "]:" << "Write header error" << std::endl;
                            thisPart->_def(thisPart, socket, events[i].data.ptr);
                            continue;
                        }
                    } else {
                        response->addHeadSend(nbytes);
                    }
            } else if (!response->bodyWriteDone()) {
                const char* buf = response->getBody()->getAdress();
                size_t nbytes = send(socket, buf, response->getBody()->length() - response->justBodySent(), 0);
                if (nbytes == -1) {
                    if (errno == EAGAIN || errno == EWOULDBLOCK) {
                        continue;
                    } else {
                        std::cerr << "[" << socket << "]:" << "Write body error" << errno << std::endl;
                        thisPart->_def(thisPart, socket, events[i].data.ptr);
                        continue;
                    }
                } else {
                    response->addBodySend(nbytes);
                    if (response->bodyWriteDone()) {
                        thisPart->output->push(writer_output(socket, true));
                        thisPart->_processList.popAddress(events[i].data.ptr);
                        thisPart->_epollEngine.deleteFd(socket);
                        shutdown(socket, 2);
                    }
                    continue;
                }
            }
        }
    }










//    for(;;) {
//        ssize_t fdCount = thisPart->_epollEngine.Wait(events);
//        for (uint32_t i = 0; i < fdCount; ++i) {
//            thisPart->_operation.lock();
//            auto it = thisPart->_processMap.find(events[i].data.fd);
//            thisPart->_operation.unlock();
//            if (it == thisPart->_processMap.end()) {
//                std::cout << "Miss" << std::endl;
//                continue;
//            }
//
//            int socket = it->second->socket;
//
//            if ((events[i].events & EPOLLERR) || (events[i].events & EPOLLHUP) || (events[i].events & EPOLLRDHUP)) {
//                std::cerr << "Writer.hpp: client socket error" << std::endl;
//                thisPart->_operation.lock();
//                thisPart->_processMap.erase(it->first);
//                thisPart->_operation.unlock();
//                thisPart->output->push(writer_output(socket, false));
//                close(socket);
//            } else if (!it->second->headersWriteDone()) {
//                const char* buf = it->second->getAdress();
//                size_t nbytes = send(socket, buf, it->second->length(), 0);
//                if (nbytes == -1) {
//                    if (errno == EAGAIN || errno == EWOULDBLOCK) {
//                        break;
//                    } else {
//                        std::cerr << "[" << socket << "]:" << "Write header error" << std::endl;
//                        thisPart->_operation.lock();
//                        thisPart->_processMap.erase(it->first);
//                        thisPart->_operation.unlock();
//                        thisPart->output->push(writer_output(socket, false));
//                        close(socket);
//                        break;
//                    }
//                } else {
//                    it->second->headersDone(true);
//                }
//            } else if (!it->second->bodyWriteDone()) {
//                const char* buf = it->second->getBody()->getAdress();
//                size_t nbytes = send(socket, buf, it->second->getBody()->length(), 0);
//                if (nbytes == -1) {
//                    if (errno == EAGAIN || errno == EWOULDBLOCK) {
//                        break;
//                    } else {
//                        std::cerr << "[" << socket << "]:" << "Write body error" << std::endl;
//                        thisPart->_operation.lock();
//                        thisPart->_processMap.erase(it->first);
//                        thisPart->_operation.unlock();
//                        thisPart->output->push(writer_output(socket, false));
//                        close(socket);
//                        break;
//                    }
//                } else {
//                    it->second->bodyDone(true);
//                }
//            } else {
//                thisPart->_operation.lock();
//                thisPart->_processMap.erase(it->first);
//                thisPart->_operation.unlock();
//                thisPart->output->push(writer_output(socket, true));
//                close(socket);
//                break;
//            }
//        }
//    }













}

template<class INP_CONTAINER, class OUT_CONTAINER>
void Writer<INP_CONTAINER, OUT_CONTAINER>::_def(Writer::this_unique &thisPart, int socket, void *ptr) {
    thisPart->_processList.popAddress(ptr);
    thisPart->output->push(writer_output(socket, false));
    thisPart->_epollEngine.deleteFd(socket);
    shutdown(socket, 2);
}

template<class INP_CONTAINER, class OUT_CONTAINER>
bool Writer<INP_CONTAINER, OUT_CONTAINER>::_setNonBlock(int fd) {
    int flags = fcntl(fd, F_GETFL, 0);

    if (fcntl(fd, F_SETFL, flags | O_NONBLOCK) == -1) {
        return false;
    }
    return true;
}

#endif //TEST_STRACE_WRITER_HPP
