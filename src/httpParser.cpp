//
// Created by kekos on 04.04.2020.
//

#include <chrono>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include "../include/httpParser.h"
#include "../include/defines.h"

extern Config* config;

std::unique_ptr<Request> HttpParser::constructRequest(std::unique_ptr<req_str_returner> requestData, SOCKET socket) {
//    std::cout << *(requestData->get()) << std::endl;
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
    std::string strUrl = _urlDecode(url);
    request->url = strUrl;

    boost::string_ref protocol = stream.getWord();
    if (protocol.length() == 0) {
        request->validRequest = false;
    }
    request->protocol = protocol;

    boost::string_ref connection = stream.getLine();
    if (connection.length() == 0) {
        request->validRequest = false;
    } else if (connection == _keepAliveStr) {
        request->keepAlive = true;
    }

    request->saveData(std::move(requestData));
    // End parsing fresh data


    request->filename = std::move(_getFilename(request->url, &request->fileDescription));
    request->fileExist = _fileExists(request->filename);
    return std::move(request);
}


PointerStringStream HttpParser::_createStream(std::string *str) {
    return PointerStringStream(str);
}

int HttpParser::fillResponse(std::string &headers, std::shared_ptr<Body> &body, std::unique_ptr<Request> &req) {
    int ret = result::error;
    std::string fileType = std::move(_getFileType(req->filename));
    std::string &typeDescription = mime_map[fileType];

    if (req->fileExist && !_access(req->filename)) {
        int code = 403;
        size_t length = _makeBadBody(code, body);

        _appendHeader(headers, length, typeDescription, req->protocol, code, req->keepAlive);
        ret = result::body_finished;
    }



    switch (req->method[0]) {
        case 'H': {
            if (!req->fileExist) {
                bool isDir = req->fileDescription.st_mode & S_IFDIR;

                int code = (isDir) ? 403 : 404;
                size_t length = _makeBadBody(code, body);

                _appendHeader(headers, length, typeDescription, req->protocol, code, req->keepAlive);
                ret = result::body_finished;
            } else {
                int code = 200;
                size_t length = (size_t) req->fileDescription.st_size;
                _appendHeader(headers, length, typeDescription, req->protocol, code, req->keepAlive);
                ret = result::body_finished;
            }
            break;
        }
        case 'G': {
            if (!req->fileExist) {
                bool isDir = req->fileDescription.st_mode & S_IFDIR;

                int code = (isDir) ? 403 : 404;
                size_t length = _makeBadBody(code, body);

                _appendHeader(headers, length, typeDescription, req->protocol, code, req->keepAlive);
                ret = result::body_finished;
            } else {
                int code = 200;
                size_t length = (size_t) req->fileDescription.st_size;
                _appendHeader(headers, length, typeDescription, req->protocol, code, req->keepAlive);
                ret = result::need_async_read;
            }
            break;
        }
        default:
            int code = 405;
            size_t length = _makeBadBody(code, body);

            _appendHeader(headers, length, typeDescription, req->protocol, code, req->keepAlive);
            ret = result::body_finished;
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

std::string HttpParser::_getFilename(std::string &url, struct stat *fileStat) {
    std::string pathname(config->rootDir());
    if (url.length() == 1) {
        pathname += _indexFile;
        stat(pathname.c_str(), fileStat);
        return std::move(pathname);
    }

    size_t paramsPos = url.find_last_of('?');

    pathname += url.substr(1, paramsPos - 1);
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

void HttpParser::_appendHeader(std::string &headers, size_t fileLength, const std::string &fileType,
                               const boost::string_ref &protocol,
                               int code, bool keepAlive) {

    std::chrono::system_clock::time_point p = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(p);
    headers.append(protocol.data(), protocol.length());
    const std::string& codeText = _getCode(code);
    const std::string connection = keepAlive ? _keepAliveResp : _closeResp;
    headers += " " + codeText + "\r\n"
            + "Server: Eeeeepollll \r\n"
            + "Date: " + std::ctime(&t)
            + connection
            + "Content-Length: " + std::to_string(fileLength) + "\r\n"
            + "Content-Type: " + fileType + "\r\n" + "\r\n";
    return;
}

std::string HttpParser::_urlDecode(boost::string_ref &url_r) {
    std::string url(url_r);
    std::string result;
    for (size_t i = 0; i < url.length(); i++) {
        if (url[i] == '+') {
            result += ' ';
        } else if (url[i] == '%') {
            int ch;
            sscanf(url.substr(i + 1,2).c_str(), "%x", &ch);
            result += static_cast<char>(ch);
            i += 2;
        } else {
            result += url[i];
        }
    }

    return result;
}

bool HttpParser::_access(std::string &filename) {
    boost::filesystem::path p(filename);
    auto canon = boost::filesystem::canonical(p);
    return canon.string().find(config->rootDir()) != std::string::npos;
}

size_t HttpParser::_makeBadBody(int code, std::shared_ptr<Body> &body) {
    const char* suitableBody;
    switch (code) {
        case 404: {
            suitableBody = notFound;
            break;
        }
        case 403: {
            suitableBody = forbidden;
            break;
        }
        default: {
            suitableBody = notAllowed;
            break;
        }
    }
    size_t length = strlen(suitableBody);
    char* bodyBuffer = (char*)malloc(length * sizeof(char));
    memcpy(bodyBuffer, suitableBody, length);
    body->reset(bodyBuffer, length, length);
    return length;
}



















