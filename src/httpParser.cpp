//
// Created by kekos on 04.04.2020.
//

#include "../include/httpParser.h"
#include "../include/namespaces.h"


void HttpParser::constructRequest(StringHolderReturn &request) {
    std::string *requestString = request.get();
    if (requestString == nullptr) {
        std::cerr << "HttpParser: request string was free" << std::endl;
        return;
    }

    PointerStringStream stream = _createStream(requestString);

    boost::string_ref method = stream.getWord();
    if (std::find(http::methods.begin(), http::methods.end(), method) == http::methods.end()) {
        return;
    }

    boost::string_ref url = stream.getWord();
    if (url.length() == 0) {
        return;
    }

    boost::string_ref protocol = stream.getWord();
    if (protocol.length() == 0) {
        return;
    }





    return;
}

PointerStringStream HttpParser::_createStream(std::string *str) {
    return PointerStringStream(str);
}


