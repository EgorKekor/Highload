//
// Created by kekor on 28.04.2020.
//

#include "../include/response.h"

Response::Response(std::string &&headers, std::string &&filename, bool isFast) :
    _headers(std::move(headers)),
    filename(std::move(filename)),
    isFast(isFast)
    {}

std::string &Response::getBody() {
    return _body;
}

std::string &Response::getHeaders() {
    return _headers;
}

void Response::putBody(std::string &&body) {
    _body = std::move(body);
}

Response::Response(std::string &&headers, bool isFast) :
        _headers(std::move(headers)),
        isFast(isFast)
{}

