//
// Created by kekos on 04.04.2020.
//

#ifndef HIGHLOAD_REQUEST_H
#define HIGHLOAD_REQUEST_H

#include <iostream>
#include <boost/utility/string_ref.hpp>
#include <memory>
#include <sys/stat.h>
#include "../include/defines.h"
#include "../include/fastList.hpp"


class Request {
public:
    typedef std::unique_ptr<std::string> fast_list_type;
    typedef FastListReturner<fast_list_type> req_str_returner;

    Request(SOCKET socket, bool corrupt = false);

    void saveData(std::unique_ptr<req_str_returner>&& sorce);
    bool isValid() { return (!memoryCorrupted || validRequest); };
    friend std::ostream& operator<<(std::ostream& os, const Request& req);

    const bool memoryCorrupted = false;
    bool validRequest = false;
    SOCKET socket;
    boost::string_ref method;
    std::string url;
    boost::string_ref protocol;

    bool fileExist = false;
    struct stat fileDescription = {};
    std::string filename;
private:
    std::unique_ptr<req_str_returner> _requestString; // Строка будет возвращена в stringHolder
};

#endif //HIGHLOAD_REQUEST_H
