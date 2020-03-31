#include <iostream>

#include "../include/fastList.h"

int main() {
    auto list = new FastListAllocator<int>(10);
    int a = 228;

    list->_new(a);
    list->_new(a);
    list->_new(a);
    list->_new(a);
    list->_new(a);

    std::cout << "Hello, World!" << std::endl;
    return 0;
}