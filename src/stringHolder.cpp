//
// Created by kekos on 03.04.2020.
//

#include "../include/stringHolder.h"

#include <utility>
#include "../include/httpParser.h"


StringHolder::StringHolder(std::shared_ptr<reader_output_container> output, size_t stringsAmount) :
    _reservedPool(stringsAmount),
    _httpParser(),
    _output(output) {
    for (size_t i = 0; i < STRINGS_AMOUNT; ++i) {
        auto reserveStr = std::make_unique<std::string>("");
        reserveStr->reserve(AVERAGE_CLIENT_MESSAGE);
        _reservedPool.push(std::move(reserveStr));
    }
}


bool StringHolder::append(SOCKET key, char *buf) {
    if (_reservedPool.size() == 0) {
        return false;
    }

    auto it = _messages.find(key);
    if (it == _messages.end()) {
        _reservedPool.peekFront()->append(buf);
        _messages.insert(
                std::pair<SOCKET, fast_list_type>(
                        key, std::move(_reservedPool.peekFront())
                )
        );
        _reservedPool.popFront();
    } else if (buf != nullptr) {
        it->second->append(buf);
        std::cout << *_messages.at(key);
    } else {
        auto returner = std::make_unique<FastListReturner<fast_list_type>>(std::move(it->second), &_reservedPool);

        auto req = std::move(_httpParser.constructRequest(std::move(returner), it->first));
        this->_output->push(std::move(req));
        _messages.erase(it->first);
    }
    return true;
}


