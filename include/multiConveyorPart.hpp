//
// Created by kekos on 15.04.2020.
//

#ifndef HIGHLOAD_MULTICONVEYORPART_HPP
#define HIGHLOAD_MULTICONVEYORPART_HPP

#include <utility>

#include "../include/conveyorPart.hpp"

int defaultGenerator(int last, int max) {
    if (++last == max) {
        return 0;
    }
    return last;
}

template <class INP_CONTAINER, class OUT_CONTAINER>
class MultiOutputConveyorPart {
public:
    MultiOutputConveyorPart(
            std::shared_ptr<INP_CONTAINER> input,
            std::shared_ptr<std::vector<std::shared_ptr<OUT_CONTAINER>>> &outputVector,
            std::function<int(int, int)> outputGenerator = defaultGenerator) :
            input(input),
            _outputVector(outputVector),
            _lastOutput(0),
            _outputSize(outputVector.size()),
            _outputGenerator(std::move(outputGenerator)) {};

    std::shared_ptr<INP_CONTAINER>& getOutput();
    std::shared_ptr<INP_CONTAINER> input;
private:
    int _lastOutput;
    int _outputSize;
    std::shared_ptr<std::vector<std::shared_ptr<OUT_CONTAINER>>&> &_outputVector;
    std::function<int(int, int)> _outputGenerator;
};

template<class INP_CONTAINER, class OUT_CONTAINER>
std::shared_ptr<INP_CONTAINER>& MultiOutputConveyorPart<INP_CONTAINER, OUT_CONTAINER>::getOutput() {
    int outputNum = _outputGenerator(_lastOutput, _outputSize);
    _lastOutput = outputNum;
    return _outputVector[outputNum];
}

#endif //HIGHLOAD_MULTICONVEYORPART_HPP
