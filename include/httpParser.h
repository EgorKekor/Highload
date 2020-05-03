//
// Created by kekos on 04.04.2020.
//

#ifndef HIGHLOAD_HTTPPARSER_H
#define HIGHLOAD_HTTPPARSER_H

#include <iostream>
#include <memory>
#include <boost/utility/string_ref.hpp>
#include <sstream>
#include <vector>
#include "../include/request.h"
#include "../include/pointerStringStream.h"
#include "../include/defines.h"
#include "../include/response.h"


// All string_ref refering to request._requestString
class HttpParser {
public:
    typedef std::unique_ptr<std::string> fast_list_type;
    typedef FastListReturner<fast_list_type> req_str_returner;

    enum result {
        error = 0,
        body_finished,
        body_need_not,
        need_async_read
    };

    HttpParser(
            std::string rootDir = "/",
            std::string indexFile = "index.html");

    std::unique_ptr<Request> constructRequest(std::unique_ptr<req_str_returner> requestData, SOCKET socket);

    int fillResponse(std::string &headers, std::shared_ptr<Body> &body, std::unique_ptr<Request> &req);


private:
    std::string _getFilename(boost::string_ref &url, struct stat *fileStat);
    const std::string& _getCode(int code);
    static std::string _getFileType(const std::string &path);

    bool _checkUrl(boost::string_ref &url);
    bool _fileExists(const std::string &path);

    PointerStringStream _createStream(std::string *str);
    void _appendHeader(
            std::string &headers,
            size_t fileLength,
            const std::string &fileType,
            const boost::string_ref &protocol,
            const std::string &code);

    std::string _rootDir;
    std::string _indexFile;
    std::unordered_map <std::string, std::string> mime_map = {
            {"txt", "text/plain"},
            {"html", "text/html"},
            {"css", "text/css"},
            {"js", "application/javascript"},
            {"jpg", "image/jpeg"},
            {"jpeg", "image/jpeg"},
            {"png", "image/png"},
            {"gif", "image/gif"},
            {"swf", "application/x-shockwave-flash"}
    };
    const char* forbidden =
            "<html>"
            "<head><title>Forbidden</title></head>"
            "<body><h1>403 Forbidden</h1></body>"
            "</html>";

    const char* notFound =
            "<html>"
            "<head><title>Not Found</title></head>"
            "<body><h1>404 Not Found</h1></body>"
            "</html>";

    const char* notAllowed =
            "<html>"
            "<head><title>Not Allowed</title></head>"
            "<body><h1>405 Method Not Allowed</h1></body>"
            "</html>";

    const char* notImplemented =
            "<html>"
            "<head><title>Not Implemented</title></head>"
            "<body><h1>501 Not Implemented</h1></body>"
            "</html>";
};

#endif //HIGHLOAD_HTTPPARSER_H
