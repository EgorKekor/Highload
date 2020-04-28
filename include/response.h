//
// Created by kekor on 28.04.2020.
//

#ifndef TEST_STRACE_RESPONSE_H
#define TEST_STRACE_RESPONSE_H

#include <sstream>

class Response {
public:
    Response(std::string &&headers, std::string &&filename, bool isFast = false);
    Response(std::string &&headers, bool isFast = false);
    void putBody(std::string &&body);
    std::string& getHeaders();
    std::string& getBody();
    std::string filename;
    bool isFast = false;
private:
    std::string _headers;
    std::string _body;
};

#endif //TEST_STRACE_RESPONSE_H
