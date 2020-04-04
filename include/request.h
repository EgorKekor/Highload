//
// Created by kekos on 04.04.2020.
//

#ifndef HIGHLOAD_REQUEST_H
#define HIGHLOAD_REQUEST_H

#include <iostream>

namespace http {
    enum class methode {
        HEAD = 0,
        GET
    };
}


class Request {
public:
    Request(std::string &body);
private:
    std::string methode;
    std::string host;
};

#endif //HIGHLOAD_REQUEST_H
