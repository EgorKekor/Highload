//
// Created by kekor on 06.05.2020.
//

#include <cassert>
#include <memory>
#include "../../include/fastList.hpp"

class Test {
public:
    Test() {
        Test::count++;
    };
    ~Test() {
        Test::count--;
    };

    static int count;
};

int Test::count = 0;


int main() {
    FastList<std::unique_ptr<Test>> list;
    while (!list.full()) {
        auto ptr = std::make_unique<Test>();
        assert(list.push(std::move(ptr)));
    }

    assert(!list.push(std::move(std::make_unique<Test>())));

    while (!list.empty()) {
        auto ptr = std::move(list.peekFront());
        list.popFront();
    }

    assert(Test::count == 0);

    return 0;
}