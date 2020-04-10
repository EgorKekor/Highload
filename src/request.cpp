//
// Created by kekos on 04.04.2020.
//

#include "../include/request.h"

Request::Request(std::unique_ptr<req_str_returner> requestString,
        boost::string_ref method,
        boost::string_ref url,
        boost::string_ref protocol,
        SOCKET socket) :
            _requestString(std::move(requestString)),
            _method(method),
            _url(url),
            _protocol(protocol),
            _socket(socket){}

Request::Request(SOCKET socket) :
        _requestString(std::make_unique<req_str_returner>(nullptr)),
        _method("BAD"),
        _url("BAD"),
        _protocol("BAD"),
        _socket(socket)
{};
