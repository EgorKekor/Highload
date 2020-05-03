//
// Created by kekos on 04.04.2020.
//

#include "../include/request.h"


Request::Request(SOCKET socket, bool corrupt) :
        _requestString(std::make_unique<req_str_returner>(nullptr)),
        memoryCorrupted(corrupt),
        socket(socket) {

}

void Request::saveData(std::unique_ptr<req_str_returner> &&source) {
    _requestString = std::move(source);
}

std::ostream &operator<<(std::ostream &os, const Request& req) {
    if (req.memoryCorrupted) {
        os << "Memory corrupted!" << std::endl;
        return os;
    }
    if (req.validRequest) {
        os << "Request invalid!" << std::endl;
    }

    os << "Socket:" << req.socket << std::endl;
    os << "Method:" << req.method << std::endl;
    os << "Url:" << req.url << std::endl;
    os << "Protocol:" << req.protocol << std::endl;
    os << "Filename:" << req.filename << std::endl;
    os << "File exist:" << req.fileExist << std::endl;
    return os;
}

