//
// Created by kekos on 04.04.2020.
//

#ifndef HIGHLOAD_REQUEST_H
#define HIGHLOAD_REQUEST_H

#include <iostream>
#include <boost/utility/string_ref.hpp>


class Request {
public:
    Request(boost::string_ref method, boost::string_ref url, boost::string_ref protocol);
private:
    std::string _method;
    std::string _url;
    std::string _protocol;
};

#endif //HIGHLOAD_REQUEST_H
