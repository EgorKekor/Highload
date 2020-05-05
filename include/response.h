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
    ~Body() {
        if (_body) {
            free(_body);
        }
    };
    Body(char *body, size_t length, size_t size);

    Body(Body const &b) = delete;
    Body(Body &b) = delete;

    Body(Body const &&other) = delete;

    Body(Body &&other) = delete;
    Body &operator=(Body&& other) = delete;

    void reset(char *body, size_t length, size_t size);

    const char * getAdress() const;
    size_t length();
    size_t size();

    size_t balance() { return length() - justWrited; };
    size_t justWrited = 0;
private:
    size_t _bodySize = 0;
    size_t _bodyLength = 0;
    char* _body;
};

class Response {
public:
    Response(Request &request, std::string &&headers, std::shared_ptr<Body> &body);
    Response(Request &request, std::string &&headers);
    size_t fileSize() { return _fileDescription.st_size; };

    void putBody(std::shared_ptr<Body> &body);
    void putBody(std::shared_ptr<Body> &&body);
    size_t getFileSize();
    std::string& getHeaders();
    std::shared_ptr<Body>& getBody();

    const char * getAdress() const { return _headers.data(); };
    size_t length() { return _headers.length(); };
    void headersDone(bool b) { _hDone = b; };
    void bodyDone(bool b) { _bDone = b; };
    bool headersWriteDone() { return _hDone; };
    bool bodyWriteDone() { return _bDone; };

    size_t balance() { return length() - justWrited; };
    size_t justWrited = 0;

    SOCKET socket;
    std::string filename;
private:
    bool _hDone = false;
    bool _bDone = false;
    struct stat _fileDescription = {};
    std::string _headers;
    std::shared_ptr<Body> _bodyPtr;
};

#endif //TEST_STRACE_RESPONSE_H
