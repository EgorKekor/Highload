//
// Created by kekor on 20.04.2020.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>
#include "../../include/cache.h"

#define FILES_AMOUNT    10
#define SIZE    64

std::string baseDir = "../tests/cache/files/";

void createFiles() {
    for (int i = 0; i < FILES_AMOUNT; ++i) {
        std::stringstream name;
        name << baseDir << "file" << i;
        std::ofstream fout(name.str());

        for (int j = 0; j < SIZE; ++j) {
            fout << i;
        }

        fout.close();
    }
}

int main() {
    createFiles();

    Cache cache1(SIZE);
    assert(*cache1.get("a") == "");

    std::string name = baseDir + "file0";
    std::ifstream fin(name);
    auto data = std::make_shared<std::string>("");
    fin >> *data;
    assert(cache1.put(name, data));
    assert(cache1.get(name) == data);
    assert(*cache1.get(name) == *data);

    std::string name2 = baseDir + "file1";
    std::ifstream fin2(name2);
    auto data2 = std::make_shared<std::string>("");
    fin2 >> *data;
    assert(cache1.put(name2, data2));
}




















