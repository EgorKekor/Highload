//
// Created by kekor on 26.04.2020.
//

#ifndef TEST_STRACE_RESPONSEMAKER_HPP
#define TEST_STRACE_RESPONSEMAKER_HPP

#include <iostream>
#include <memory>
#include "../include/defines.h"
#include "../include/request.h"
#include "../include/httpParser.h"
#include "../include/response.h"
#include "../include/simpleConveyorPart.hpp"
#include "../include/asyncReader.h"

template <class INP_CONTAINER, class OUT_CONTAINER>
class ResponseMaker : public SimpleConveyorPart<INP_CONTAINER, OUT_CONTAINER> {
public:
    typedef CONVEYOR_20_INPUT this_input;
    typedef CONVEYOR_20_OUTPUT uptr_this_output;
    typedef std::unique_ptr<ResponseMaker<INP_CONTAINER, OUT_CONTAINER>> this_unique;
    typedef ResponseMaker<INP_CONTAINER, OUT_CONTAINER> this_type;

    ~ResponseMaker() {
        std::cout << "ResponseMaker destroyed" << std::endl;
    };
    ResponseMaker(
            std::shared_ptr<INP_CONTAINER> &input,
            std::shared_ptr<OUT_CONTAINER> &output) :
                _httpParser(),
                SimpleConveyorPart<INP_CONTAINER, OUT_CONTAINER>(input, output) {
        std::thread workerThr(_readWorker, this_unique(this));
        workerThr.detach();
    };
    void push(std::unique_ptr<Response> response);
private:
    HttpParser _httpParser;
    AsyncReader _asyncReader;
    static void _readWorker(this_unique thisPart);
};

template<class INP_CONTAINER, class OUT_CONTAINER>
void ResponseMaker<INP_CONTAINER, OUT_CONTAINER>::_readWorker(ResponseMaker::this_unique thisPart) {
    for(;;) {
        auto request = std::move(thisPart->input->blockPeek());

        std::string headers;
        auto body = std::make_shared<Body>(nullptr, 0, 0);
        int result = thisPart->_httpParser.fillResponse(headers, body, request);

        if (result == HttpParser::result::error) {
            std::cerr << "Bad request {" << std::endl << *request << "}" << std::endl;
        } else if (result == HttpParser::result::body_finished) {
            //std::cout << "body_finished" << std::endl;
            auto response = std::make_unique<Response>(*request , std::move(headers), body);
            thisPart->output->push(std::move(response));
        } else if (result == HttpParser::result::body_need_not) {
            //std::cout << "body_need_not" << std::endl;
            auto response = std::make_unique<Response>(*request , std::move(headers));
            thisPart->output->push(std::move(response));
        } else if (result == HttpParser::result::need_async_read) {
            //std::cout << "need_async_read" << std::endl;
            auto response = std::make_unique<Response>(*request , std::move(headers));
            thisPart->_asyncReader.push(
                    std::move(response),
                    [& thisPart](std::unique_ptr<Response> response) {
                        thisPart->output->push(std::move(response));
                    }
            );
        }

        thisPart->input->blockPop();
        //break;
    }
}

template<class INP_CONTAINER, class OUT_CONTAINER>
void ResponseMaker<INP_CONTAINER, OUT_CONTAINER>::push(std::unique_ptr<Response> response) {
    this->output->push(std::move(response));
}

#endif //TEST_STRACE_RESPONSEMAKER_HPP
