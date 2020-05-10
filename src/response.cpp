//
// Created by kekor on 28.04.2020.
//

#include "../include/response.h"

#include <utility>

Response::Response(Request &request, std::string &&headers, std::shared_ptr<Body> &body) :
    _headers(std::move(headers)),
    _bodyPtr(body),
    socket(request.socket),
    filename(request.filename),
    keepAlive(request.keepAlive),
    _fileDescription(request.fileDescription) {}

Response::Response(Request &request, std::string &&headers) :
    _headers(std::move(headers)),
    socket(request.socket),
    filename(request.filename),
    _fileDescription(request.fileDescription),
    keepAlive(request.keepAlive),
    _bodyPtr(std::make_shared<Body>(nullptr, 0, 0))
{}

std::shared_ptr<Body>& Response::getBody() {
    return _bodyPtr;
}

std::string &Response::getHeaders() {
    return _headers;
}

void Response::putBody(std::shared_ptr<Body> &body) {
    _bodyPtr = body;
}

void Response::putBody(std::shared_ptr<Body> &&body) {
    _bodyPtr = std::move(body);
}

void Response::addBodySend(size_t sended) {
    _bodySended += sended;
    if (_bodySended >= _bodyPtr->length()) {
        _bDone = true;
    }
}

void Response::addHeadSend(size_t sended) {
    _headSended += sended;
    if (_headSended >= _headers.length()) {
        _hDone = true;
    }
}


// =================================================

Body::Body(char *body, size_t length, size_t size) :
    _body(body),
    _bodySize(size),
    _bodyLength(length){}

const char* Body::getAdress() const {
    return _body;
}

size_t Body::length() {
    return _bodyLength;
}


//Body::Body(Body &&other) :
//    _body(std::move(other._body)),
//    _bodySize(other._bodySize),
//    _bodyLength(other._bodyLength){}

void Body::reset(char *body, size_t length, size_t size) {
    if (_body) {
        free(_body);
    }
    _body = body;
    _bodyLength = length;
    _bodySize = size;
}

//Body &Body::operator=(Body &&other) {
//    _body = std::move(other._body);
//    _bodySize = other._bodySize;
//    _bodyLength = other._bodyLength;
//    return *this;
//}


size_t Body::size() {
    return _bodySize;
}

