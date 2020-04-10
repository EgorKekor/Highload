//
// Created by kekos on 04.04.2020.
//

#ifndef HIGHLOAD_REQUEST_H
#define HIGHLOAD_REQUEST_H

#include <iostream>
#include <boost/utility/string_ref.hpp>
#include <memory>
#include "../include/defines.h"
#include "../include/fastList.hpp"


class Request {
public:
    typedef std::unique_ptr<std::string> fast_list_type;
    typedef FastListReturner<fast_list_type> req_str_returner;

    Request(SOCKET socket);
    Request(std::unique_ptr<req_str_returner> requestStringReturner,
            boost::string_ref method,
            boost::string_ref url,
            boost::string_ref protocol,
            SOCKET socket);
private:
    std::unique_ptr<req_str_returner> _requestString;
    std::string _method;
    std::string _url;
    std::string _protocol;
    SOCKET _socket;
};

#endif //HIGHLOAD_REQUEST_H
