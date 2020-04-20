//
// Created by kekor on 20.04.2020.
//

#include <vector>
#include <climits>
#include "../include/cache.h"


std::shared_ptr<std::string> Cache::get(std::string fileName) {
    auto it = _cache.find(fileName);
    if (it == _cache.end()) {
        return std::make_shared<std::string>("");
    }

    auto end = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - _start);

    if (elapsed >= RATE_INTERVAL) {
        _start = std::chrono::steady_clock::now();
        _cacheSizeSorted.erase(it->second.last_rate);
        it->second.last_rate = it->second.require_count;
        it->second.require_count = 0;
        _cacheSizeSorted.insert(std::pair<size_t, map_iterator>(it->second.last_rate, it));
    }

    it->second.require_count++;

    return it->second.s_ptr;
}


bool Cache::put(std::string fileName, std::shared_ptr<std::string> sPtr) {
    if (_currentSize >= _cache_size) {
        auto deletedRate = _deletedRates.find(fileName);
        if (deletedRate != _deletedRates.end()) {
            auto currentMinRate = _getMinRate();
            bool swap = true;
            size_t copySize = _currentSize;

            while (copySize >= _cache_size) {
                if (deletedRate->second > currentMinRate->second.last_rate) {
                    _recordForDelete.push_back(currentMinRate);
                    copySize -= currentMinRate->second.s_ptr->length();
                    currentMinRate = _getMinRate();
                } else {
                    swap = false;
                    break;
                }
            }

            if (swap) {
                _currentSize = copySize;
                bool result = _insert(fileName, sPtr);
                return result;
            }
            return false;
        } else {
            return _tryInsert(fileName, sPtr);
        }
    }
    return _tryInsert(fileName, sPtr);
}

Cache::Cache(size_t sz) : _cache_size(sz) {
    _start = std::chrono::steady_clock::now();
    _recordForDelete.reserve(1024);
}

Cache::map_iterator Cache::_getMinRate() {
    return _cacheSizeSorted.begin()->second;
}




bool Cache::_tryInsert(std::string &fileName, std::shared_ptr<std::string> &sPtr) {
    auto currentMinRate = _getMinRate();

    bool swap = true;
    size_t copySize = _currentSize;
    while (copySize >= _cache_size) {
        if (_cache.size() == _recordForDelete.size()) {
            swap = false;
            break;
        }
        _recordForDelete.push_back(currentMinRate);
        copySize -= currentMinRate->second.s_ptr->length();
        currentMinRate = _getMinRate();
    }

    if (swap) {
        _currentSize = copySize;
        return _insert(fileName, sPtr);
    }
    return false;
}


bool Cache::_insert(std::string &fileName, std::shared_ptr<std::string> &sPtr) {
    for (auto it : _recordForDelete) {
        _deletedRates.insert(std::pair<std::string, size_t>(fileName, it->second.last_rate));
        _cacheSizeSorted.erase(it->second.last_rate);
        _cache.erase(it);
    }
    _recordForDelete.clear();

    auto newIter = _cache.insert(std::pair<std::string, CacheRecord>(fileName,{sPtr, LONG_MAX, 0}));
    _cacheSizeSorted.insert(std::pair<size_t, map_iterator>(LONG_MAX, newIter.first));
    _currentSize += sPtr->length();
    return true;
}
