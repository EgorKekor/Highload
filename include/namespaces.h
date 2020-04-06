//
// Created by kekos on 06.04.2020.
//

#ifndef HIGHLOAD_NAMESPACES_H
#define HIGHLOAD_NAMESPACES_H

#include <iostream>
#include <vector>

namespace http {
    inline std::vector<std::string> methods {
            std::string("HEAD"),
            std::string("GET"),
    };
}

#endif //HIGHLOAD_NAMESPACES_H
