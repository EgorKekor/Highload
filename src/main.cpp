#include <iostream>

#include "../include/fastList.h"

#define TYPE    int

bool foo(TYPE &value) {
    std::cout << value << " ";
    return true;
}

int main() {
    auto list = new FastList<TYPE>(100);

    int i = 0;
    for (;; ++i) {
        if (!list->push(i)) {
            break;
        }
        list->traverseAll(foo);
    }

    std::cout << i << std::endl;
    return 0;
}