//
// Created by kekor on 28.04.2020.
//

#ifndef TEST_STRACE_RESPONSE_H
#define TEST_STRACE_RESPONSE_H

#include <sstream>
#include <sys/stat.h>
#include "../include/defines.h"
#include "request.h"

class Body {
public:
    Body(char* body, size_t length);

    Body(Body const &b) = delete;
    Body(Body &b) = delete;

    Body(Body const &&other) = delete;

    Body(Body &&other);
    Body &operator=(Body&& other);

    void reset(char* body, size_t length);
    void resetSize(size_t newSize);
    unique_ptr_free<char> getBody();
    char* getBodyPtr();
    size_t getSize();
private:
    size_t _bodySize = 0;
    unique_ptr_free<char> _body;
};

class Response {
public:
    Response(Request &request, std::string &&headers, Body body);
    Response(Request &request, std::string &&headers);
    size_t fileSize() { return _fileDescription.st_size; };

    void putBody(Body &&body);
    size_t getFileSize();
    std::string& getHeaders();
    Body& getBody();

    SOCKET socket;
    std::string filename;
private:
    struct stat _fileDescription = {};
    std::string _headers;
    Body _body;
};

#endif //TEST_STRACE_RESPONSE_H
