//
// Created by kekor on 20.04.2020.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>
#include <unistd.h>
#include <thread>
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

std::string getName(int i) {
    std::stringstream name;
    name << baseDir << "file" << i;
    return name.str();
}

std::shared_ptr<std::string> getData(std::string name, int i) {
    std::ifstream fin(name);
    auto data = std::make_shared<std::string>("");
    fin >> *data;
    return data;
}

void test1() {
    createFiles();

    Cache cache1(SIZE);
    assert(*cache1.get("a") == "");

    auto name = getName(0);
    auto data = getData(name, 0);
    assert(cache1.put(name, data));
    assert(cache1.get(name) == data);
    assert(*cache1.get(name) == *data);

    auto name1 = getName(1);
    auto data1 = getData(name1, 1);
    assert(!cache1.put(name1, data1));

    std::this_thread::sleep_for(RATE_INTERVAL);

    assert(cache1.put(name1, data1));

    std::this_thread::sleep_for(RATE_INTERVAL);

    assert(cache1.put(name, data));

    std::this_thread::sleep_for(RATE_INTERVAL);

    assert(!cache1.put(name1, data1));
}

void test2() {
    Cache cache(SIZE * FILES_AMOUNT / 2);

    for (int i = 0; i < FILES_AMOUNT / 2; ++i) {
        auto name = getName(i);
        auto data = getData(name, i);
        assert(cache.put(name, data));

        for (int j = 0; j < i + 1; ++j) {
            cache.get(name);
        }
    }


    std::this_thread::sleep_for(RATE_INTERVAL);

    for (int i = FILES_AMOUNT / 2; i < FILES_AMOUNT; ++i) {
        auto name = getName(i);
        auto data = getData(name, i);
        assert(cache.put(name, data));
    }

    for (int i = 0; i < FILES_AMOUNT / 2; ++i) {
        auto name = getName(i);
        auto data = getData(name, i);
        assert(!cache.put(name, data));
    }
    std::this_thread::sleep_for(RATE_INTERVAL);
    for (int i = FILES_AMOUNT / 2 - 1; i >= 0; --i) {
        auto name = getName(i);
        auto data = getData(name, i);
        assert(cache.put(name, data));
    }
}

int main() {
    test1();
    test2();
}




















