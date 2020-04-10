//
// Created by kekos on 04.04.2020.
//

#ifndef HIGHLOAD_HTTPPARSER_H
#define HIGHLOAD_HTTPPARSER_H

#include <iostream>
#include <memory>
#include <boost/utility/string_ref.hpp>
#include <sstream>
#include <vector>
#include "../include/request.h"
#include "../include/pointerStringStream.h"
#include "../include/defines.h"


class HttpParser {
public:
    typedef std::unique_ptr<std::string> fast_list_type;
    typedef FastListReturner<fast_list_type> req_str_returner;

    HttpParser() = default;
    std::unique_ptr<Request> constructRequest(std::unique_ptr<req_str_returner> request, SOCKET socket);
private:
    PointerStringStream _createStream(std::string *str);
};

#endif //HIGHLOAD_HTTPPARSER_H
