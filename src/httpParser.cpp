//
// Created by kekos on 04.04.2020.
//

#include "../include/httpParser.h"
#include "../include/defines.h"


std::unique_ptr<Request> HttpParser::constructRequest(std::unique_ptr<req_str_returner> request, SOCKET socket) {
    if (request.get() == nullptr) {
        std::cerr << "HttpParser: request string was free" << std::endl;
        return std::make_unique<Request>(socket);
    }

    PointerStringStream stream = _createStream(request->get().get());

    boost::string_ref method = stream.getWord();
    if (std::find(http::methods.begin(), http::methods.end(), method) == http::methods.end()) {
        return std::make_unique<Request>(socket);
    }

    boost::string_ref url = stream.getWord();
    if (url.length() == 0) {
        return std::make_unique<Request>(socket);
    }

    boost::string_ref protocol = stream.getWord();
    if (protocol.length() == 0) {
        return std::make_unique<Request>(socket);
    }

    return std::make_unique<Request>(std::move(request), method, url, protocol, socket);
}

PointerStringStream HttpParser::_createStream(std::string *str) {
    return PointerStringStream(str);
}


