//
// Created by kekos on 04.04.2020.
//

#include <chrono>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include "../include/httpParser.h"
#include "../include/defines.h"

extern Config* config;

std::unique_ptr<Request> HttpParser::constructRequest(std::unique_ptr<req_str_returner> requestData, SOCKET socket) {
    if (requestData.get() == nullptr) {
        std::cerr << "HttpParser: requestData string was free" << std::endl;
        return std::make_unique<Request>(socket, true);
    }
    auto request = std::make_unique<Request>(socket, false);
    request->validRequest = true;

    PointerStringStream stream = _createStream(requestData->get().get());

    boost::string_ref method = stream.getWord();
    if (std::find(http::methods.begin(), http::methods.end(), method) == http::methods.end()) {
        request->validRequest = false;
    }
    request->method = method;

    boost::string_ref url = stream.getWord();
    if (url.length() == 0) {
        request->validRequest = false;
    }
    request->url = url;

    boost::string_ref protocol = stream.getWord();
    if (protocol.length() == 0) {
        request->validRequest = false;
    }
    request->protocol = protocol;

    request->saveData(std::move(requestData));
    // End parsing fresh data


    request->filename = std::move(_getFilename(url, &request->fileDescription));
    request->fileExist = _fileExists(request->filename);
    return std::move(request);
}


PointerStringStream HttpParser::_createStream(std::string *str) {
    return PointerStringStream(str);
}

int HttpParser::fillResponse(std::string &headers, std::shared_ptr<Body> &body, std::unique_ptr<Request> &req) {
    int ret = result::error;

    switch (req->method[0]) {
        case 'H': {
            size_t length = 0;
            std::string fileType = std::move(_getFileType(req->filename));
            std::string &typeDescription = mime_map[fileType];

            if (!req->fileExist) {
                bool isDir = req->fileDescription.st_mode & S_IFDIR;

                const auto code = (isDir) ? _getCode(403) : _getCode(404);
                const char* suitableBody = (isDir) ? forbidden : notFound;
                length = strlen(suitableBody);
                char* bodyBuffer = (char*)malloc(length * sizeof(char));
                memcpy(bodyBuffer, suitableBody, length * sizeof(char));
                body->reset(bodyBuffer, length, length);

                _appendHeader(headers, length, typeDescription, req->protocol, code);
                ret = result::body_finished;
            } else {
                const auto code = _getCode(200);
                length = (size_t) req->fileDescription.st_size;
                _appendHeader(headers, length, fileType, req->protocol, code);
                ret = result::need_async_read;
            }
            break;
        }
        case 'G': {
            size_t length = 0;
            std::string fileType = std::move(_getFileType(req->filename));
            std::string &typeDescription = mime_map[fileType];

            if (!req->fileExist) {
                bool isDir = req->fileDescription.st_mode & S_IFDIR;

                const auto code = (isDir) ? _getCode(403) : _getCode(404);
                const char* suitableBody = (isDir) ? forbidden : notFound;
                length = strlen(suitableBody);
                char* bodyBuffer = (char*)malloc(length * sizeof(char));
                memcpy(bodyBuffer, suitableBody, length);
                body->reset(bodyBuffer, length, length);

                _appendHeader(headers, length, typeDescription, req->protocol, code);
                ret = result::body_finished;
            } else {
                const auto code = _getCode(200);
                length = (size_t) req->fileDescription.st_size;
                _appendHeader(headers, length, fileType, req->protocol, code);
                ret = result::need_async_read;
            }
            break;
        }
        default:
            break;
    }

    return ret;
}

const std::string& HttpParser::_getCode(int code) {
    static std::string def("");
    static std::string C_200("200 OK");
    static std::string C_403("403 Forbidden");
    static std::string C_404("404 Not Found");
    static std::string C_405("405 Method Not Allowed");
    static std::string C_501("501 Not Implemented");
    switch (code) {
        case 200:
            return C_200;
        case 403:
            return C_403;
        case 404:
            return C_404;
        case 405:
            return C_405;
        case 501:
            return C_501;
        default:
            return def;
    }
}

HttpParser::HttpParser(std::string rootDir, std::string indexFile) : _rootDir(rootDir), _indexFile(indexFile) {

}

std::string HttpParser::_getFilename(boost::string_ref &url, struct stat *fileStat) {
    std::string pathname(config->rootDir());
    if (url.length() == 1) {
        pathname += _indexFile;
        stat(pathname.c_str(), fileStat);
        return std::move(pathname);
    }

    pathname += std::string(url.substr(1));
    bool isDir = ((stat(pathname.c_str(), fileStat) == 0) && (fileStat->st_mode & S_IFDIR));
    if (isDir) {
        if (pathname.back() != '/') {
            pathname += '/';
        }
        pathname += _indexFile;
    }
    stat(pathname.c_str(), fileStat);

    return std::move(pathname);
}


bool HttpParser::_checkUrl(boost::string_ref &url) {
    size_t pos = url.find("http://");
    if ((pos == std::string::npos) || (pos != 0)) {
        return false;
    }
    return true;
}

bool HttpParser::_fileExists(const std::string &path) {
    return access(path.c_str(), 0) != -1;}


std::string HttpParser::_getFileType(const std::string &path) {
    size_t pos = path.find_last_of('.');
    return std::move((pos != std::string::npos) ? path.substr(pos + 1) : "txt");
}

void HttpParser::_appendHeader(std::string &headers, size_t fileLength,
                               const std::string &fileType, const boost::string_ref &protocol, const std::string &code) {

    std::chrono::system_clock::time_point p = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(p);
    headers.append(protocol.data(), protocol.length());
    headers += " " + code + "\r\n"
            + "Server: Eeeeepollll \r\n"
            + "Date: " + std::ctime(&t)
            + "Connection: close\r\n"
            + "Content-Length: " + std::to_string(fileLength) + "\r\n"
            + "Content-Type: " + fileType + "\r\n" + "\r\n";
}



















