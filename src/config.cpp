//
// Created by kekor on 02.05.2020.
//

#include "../include/config.h"


Config::Config() :
        _rootDir(ROOT_DIR)
{

}

const std::string &Config::rootDir() {
    return _rootDir;
}

const size_t Config::getAlign() {
    return 512;
}
