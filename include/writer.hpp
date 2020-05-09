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
    typedef CONVEYOR_30_INPUT writer_input;
    typedef CONVEYOR_30_OUTPUT writer_output;
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
    FastList<CONVEYOR_20_OUTPUT> _processList;
    std::map<SOCKET, CONVEYOR_20_OUTPUT> _processMap;
    Epoll _epollEngine;
    static void _readWorker(this_unique thisPart);
    static void _writeWorker(this_unique thisPart);
    std::mutex _operation;
    static bool _setNonBlock(int fd);
    static bool _setBlock(int fd);
    void _def(Writer::this_unique &thisPart, int socket, void *ptr);
};

template<class INP_CONTAINER, class OUT_CONTAINER>
void Writer<INP_CONTAINER, OUT_CONTAINER>::_readWorker(Writer::this_unique thisPart) {
    struct sigaction sig{SIG_IGN};
    sigaction(SIGPIPE, &sig, NULL);
    for(;;) {
        auto response = std::move(thisPart->input->blockPeek());
        int fd = response->socket;

        int epollFd = thisPart->_epollEngine.Epollfd();
        thisPart->_processList.push(std::move(response));
        void* respAddr = thisPart->_processList.getBack();
        thisPart->_epollEngine.AddFd(fd, epollFd, respAddr);

        thisPart->tryYield();
        thisPart->input->blockPop();


// Turbo mode
//
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

    size_t maxEvents = 0;
    auto start = std::chrono::steady_clock::now();
    auto end = std::chrono::steady_clock::now();

    for(;;) {
        ssize_t fdCount = thisPart->_epollEngine.Wait(events);
        for (uint32_t i = 0; i < fdCount; ++i) {
            if ((fdCount > maxEvents) && (fdCount > 1)) {
                if (i == 0) {
                    start = std::chrono::steady_clock::now();
                } else if (i == fdCount - 1) {
                    maxEvents = fdCount;
                    end = std::chrono::steady_clock::now();
                    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
                    std::cout << "Epoll for " << fdCount << " operation " << "spent " << elapsed.count() << "ms" << std::endl;
                }
            }
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
            } else {
                for (;;) {
                    if (!response->headersWriteDone()) {
                        const char *buf = response->getAdress();

                        const char *bufOffset = &buf[response->justHeadSent()];
                        size_t nbytes = write(socket, bufOffset, response->headBalance());
                        if (nbytes == -1) {
                            if (errno == EAGAIN || errno == EWOULDBLOCK) {
                                break;
                            } else {
                                std::cerr << "[" << socket << "]:" << "Write header error" << std::endl;
                                thisPart->_def(thisPart, socket, events[i].data.ptr);
                                break;
                            }
                        } else {
                            response->addHeadSend(nbytes);
                            continue;
                        }
                    } else if (!response->bodyWriteDone()) {
                        const char* buf = response->getBody()->getAdress();

                        const char *bufOffset = &buf[response->justBodySent()];
                        size_t nbytes = write(socket, bufOffset, response->bodyBalance());
                        if (nbytes == -1) {
                            if (errno == EAGAIN || errno == EWOULDBLOCK) {
                                //std::cout << "EWOULDBLOCK" << std::endl;
                                break;
                            } else {
                                std::cerr << "[" << socket << "]:" << "Write body error" << std::endl;
                                thisPart->_def(thisPart, socket, events[i].data.ptr);
                                break;
                            }
                        } else {
                            response->addBodySend(nbytes);
                            continue;
                        }
                    } else {
                        //thisPart->output->push(writer_output(socket, true));
                        thisPart->_processList.popAddress(events[i].data.ptr);
                        thisPart->_epollEngine.deleteFd(socket);
                        shutdown(socket, 2);
                        //close(socket);
                        break;
                    }
                }
            }
        }
    }


}

template<class INP_CONTAINER, class OUT_CONTAINER>
void Writer<INP_CONTAINER, OUT_CONTAINER>::_def(Writer::this_unique &thisPart, int socket, void *ptr) {
    thisPart->_processList.popAddress(ptr);
    //thisPart->output->push(writer_output(socket, false));
    thisPart->_epollEngine.deleteFd(socket);
    shutdown(socket, 2);
    //close(socket);
}

template<class INP_CONTAINER, class OUT_CONTAINER>
bool Writer<INP_CONTAINER, OUT_CONTAINER>::_setNonBlock(int fd) {
    int flags = fcntl(fd, F_GETFL, 0);

    if (fcntl(fd, F_SETFL, flags | O_NONBLOCK) == -1) {
        return false;
    }
    return true;
}

template<class INP_CONTAINER, class OUT_CONTAINER>
bool Writer<INP_CONTAINER, OUT_CONTAINER>::_setBlock(int fd) {
    int flags = fcntl(fd, F_GETFL, 0);

    if (fcntl(fd, F_SETFL, flags & ~O_NONBLOCK) == -1) {
        return false;
    }
    return true;
}

#endif //TEST_STRACE_WRITER_HPP
