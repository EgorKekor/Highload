//
// Created by kekor on 28.04.2020.
//

#include "../include/response.h"

Response::Response(Request &request, std::string &&headers, Body body) :
    _headers(std::move(headers)),
    _body(std::move(body)),
    socket(request.socket),
    filename(request.filename),
    _fileDescription(request.fileDescription) {}

Response::Response(Request &request, std::string &&headers) :
    _headers(std::move(headers)),
    socket(request.socket),
    filename(request.filename),
    _fileDescription(request.fileDescription),
    _body(nullptr, 0)
{}

Body& Response::getBody() {
    return _body;
}

std::string &Response::getHeaders() {
    return _headers;
}

void Response::putBody(Body &&body) {
    _body = std::move(body);
}



size_t Response::getFileSize() {
    return 0;
}

Body::Body(char *body, size_t length) :
    _body(make_unique_free<char>(body)),
    _bodySize(length) {}

unique_ptr_free<char> Body::getBody() {
    return std::move(_body);
}

size_t Body::getSize() {
    return _bodySize;
}


Body::Body(Body &&other) :
    _body(std::move(other._body)),
    _bodySize(other._bodySize) {}

void Body::reset(char* body, size_t length) {
    _body.reset(body);
    _bodySize = length;
}

Body &Body::operator=(Body &&other) {
    _body = std::move(other._body);
    _bodySize = other._bodySize;
    return *this;
}

char* Body::getBodyPtr() {
    return _body.get();
}

void Body::resetSize(size_t newSize) {
    _bodySize = newSize;
}
