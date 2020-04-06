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
#include "../include/returns.h"


class StringHolderReturn;


class HttpParser {
public:
    HttpParser() = default;
    void constructRequest(StringHolderReturn &request);
private:
    PointerStringStream _createStream(std::string *str);
};

#endif //HIGHLOAD_HTTPPARSER_H
