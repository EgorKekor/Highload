//
// Created by kekos on 04.04.2020.
//

#ifndef HIGHLOAD_HTTPMANAGER_H
#define HIGHLOAD_HTTPMANAGER_H

#include <iostream>
#include <memory>
#include "../include/request.h"

class HttpManager {
public:
    std::unique_ptr<Request> constructRequest(std::string &body);
};

#endif //HIGHLOAD_HTTPMANAGER_H
