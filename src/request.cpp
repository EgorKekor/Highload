//
// Created by kekos on 04.04.2020.
//

#include "../include/request.h"

Request::Request(boost::string_ref method, boost::string_ref url, boost::string_ref protocol) :
        _method(method),
        _url(url),
        _protocol(protocol){

};
