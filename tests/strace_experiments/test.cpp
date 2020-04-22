//
// Created by kekor on 21.04.2020.
//

#include <string>
#include <chrono>
#include <iostream>

#define LINES       1024 * 10
#define LINE_LEN    128 * 10
#define ITERATIONS  100

void bad() {
    std::string kek(LINE_LEN, 'i');
    std::string f;
    for (int i = 0; i < LINES; ++i) {
        f += kek;
    }
    return;
}

void good() {
    std::string kek(LINE_LEN, 'i');
    std::string f;
    f.reserve(LINE_LEN * LINES);
    for (int i = 0; i < LINES; ++i) {
        f += kek;
    }
    return;
}


int main() {
    int nanosecondsCounter = 0;

    auto start = std::chrono::steady_clock::now();
    auto end = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    for (int i = 0; i < ITERATIONS; ++i) {
        start = std::chrono::steady_clock::now();
        bad();
        end = std::chrono::steady_clock::now();
        elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        nanosecondsCounter += elapsed.count();
    }

    double average = (double)nanosecondsCounter / ITERATIONS;
    std::cout << "No reserve average time: " << average << std::endl;

    nanosecondsCounter = 0;
    for (int i = 0; i < ITERATIONS; ++i) {
        start = std::chrono::steady_clock::now();
        good();
        end = std::chrono::steady_clock::now();
        elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        nanosecondsCounter += elapsed.count();
    }

    average = (double)nanosecondsCounter / ITERATIONS;
    std::cout << "Reserve average time: " << average << std::endl;
}