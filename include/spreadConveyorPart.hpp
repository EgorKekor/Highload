//
// Created by kekos on 15.04.2020.
//

#ifndef HIGHLOAD_SPREADCONVEYORPART_HPP
#define HIGHLOAD_SPREADCONVEYORPART_HPP

#include <utility>

inline int defaultGenerator(int curr, int max) {
    if (curr == max - 1) {
        curr = 0;
        return 0;
    }
    return ++curr;
}

template <class INP_CONTAINER, class OUT_CONTAINER>
class SpreadConveyorPart final {
public:
    typedef std::unique_ptr<SpreadConveyorPart<INP_CONTAINER, OUT_CONTAINER>> this_unique;

    SpreadConveyorPart(
            std::shared_ptr<INP_CONTAINER> &input,
            std::vector<std::shared_ptr<OUT_CONTAINER>> &outputVector,
            std::function<int(int, int)> outputGenerator = defaultGenerator) :
            _input(input),
            _outputVector(outputVector),
            _currOutput(0),
            _outputSize(outputVector.size()),
            _outputGenerator(std::move(outputGenerator)) {
        std::thread workerThr(_readWorker, this_unique(this));
        workerThr.detach();
    };

private:
    int _currOutput;
    int _outputSize;
    std::shared_ptr<INP_CONTAINER> &_input;
    std::vector<std::shared_ptr<OUT_CONTAINER>> &_outputVector;
    std::function<int(int, int)> _outputGenerator;

    static void _readWorker(this_unique thisPart);
};

template<class INP_CONTAINER, class OUT_CONTAINER>
void SpreadConveyorPart<INP_CONTAINER, OUT_CONTAINER>::_readWorker(this_unique thisPart) {
    for(;;) {
        auto inputData = thisPart->_input->blockPeek();

        thisPart->_outputVector[thisPart->_currOutput]->push(inputData);

        thisPart->_currOutput = thisPart->_outputGenerator(thisPart->_currOutput, thisPart->_outputSize);
    }
}

// =====================================================

template <class INP_CONTAINER, class OUT_CONTAINER>
class MoveSpreadConveyorPart final {
public:
    typedef std::unique_ptr<MoveSpreadConveyorPart<INP_CONTAINER, OUT_CONTAINER>> this_unique;

    MoveSpreadConveyorPart(
            std::shared_ptr<INP_CONTAINER> &input,
            std::vector<std::shared_ptr<OUT_CONTAINER>> &outputVector,
            std::function<int(int, int)> outputGenerator = defaultGenerator) :
            _input(input),
            _outputVector(outputVector),
            _currOutput(0),
            _outputSize(outputVector.size()),
            _outputGenerator(std::move(outputGenerator)) {
        std::thread workerThr(_readWorker, this_unique(this));
        workerThr.detach();
    };

private:
    int _currOutput;
    int _outputSize;
    std::shared_ptr<INP_CONTAINER> &_input;
    std::vector<std::shared_ptr<OUT_CONTAINER>> &_outputVector;
    std::function<int(int, int)> _outputGenerator;

    static void _readWorker(this_unique thisPart);
};

template<class INP_CONTAINER, class OUT_CONTAINER>
void MoveSpreadConveyorPart<INP_CONTAINER, OUT_CONTAINER>::_readWorker(this_unique thisPart) {
    for(;;) {
        auto inputData = std::move(thisPart->_input->blockPeek());

        thisPart->_outputVector[thisPart->_currOutput]->push(std::move(inputData));

        auto temp = thisPart->_outputGenerator(thisPart->_currOutput, thisPart->_outputSize);
        thisPart->_currOutput = temp;
    }
}





#endif //HIGHLOAD_SPREADCONVEYORPART_HPP
