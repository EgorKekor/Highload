//
// Created by kekor on 20.04.2020.
//

#include <vector>
#include <climits>
#include <iostream>
#include "../include/cache.h"

#define NOT_NEW_RECORD

std::shared_ptr<Body> Cache::get(std::string &fileName) {
//    std::cout << "GET:" << fileName << "=====================" << std::endl;
    _printCache("get");
    _printCacheSizeSorted("get");
    _printDeleted("get");

    auto itTarget = _cache.find(fileName);
    if (itTarget == _cache.end()) {
        return _fake;
    }
    _calculateRate();
    itTarget->second.require_count++;

    _printCache("get");
    _printCacheSizeSorted("get");
    _printDeleted("get");
    return itTarget->second.body;
}


bool Cache::put(std::string &fileName, std::shared_ptr<Body>& body) {
//    std::cout << "PUT:" << fileName << "=====================" << std::endl;
    _printCache("put");
    _printCacheSizeSorted("put");
    _printDeleted("put");

    _calculateRate();

    if (_currentSize + body->size() > _cache_size) {
//        std::cout << "Cache don't had place, need clear!" << std::endl;
        auto deletedRecord = _deletedRecords.find(fileName);
        if (deletedRecord != _deletedRecords.end()) {
            return _deletedInsert(fileName, body, deletedRecord);
        } else {
            return _regularInsert(fileName, body);
        }
    }
//    std::cout << "Put will done" << std::endl;
    _currentSize += body->size();
    bool result = _insert(fileName, body, false);
    _printCache("put");
    _printCacheSizeSorted("put");
    _printDeleted("put");
    return result;
}

Cache::Cache(size_t sz) : _cache_size(sz), _fake(std::make_shared<Body>(nullptr, 0, 0)) {
    _start = std::chrono::steady_clock::now();
    _recordForDelete.reserve(1024);
}






bool Cache::_regularInsert(std::string &fileName, std::shared_ptr<Body>& body) {
//    std::cout << "This record insert firstly:" << fileName << std::endl;
    auto currentMinRate = _sortedCache.begin();

    bool swap = true;
    size_t copySize = _currentSize;
    while (copySize + body->size() > _cache_size) {
        if ((_cache.size() == _recordForDelete.size()) || (currentMinRate->second->second.last_rate >= LONG_MAX - 1)) {
//            std::cout << "No put: this record to big for insert OR This record will replace over not calculated records" << std::endl;
            swap = false;
            break;
        }
        _recordForDelete.push_back(currentMinRate->second);
        copySize -= currentMinRate->second->second.body->size();
        currentMinRate++;
    }

    if (swap) {
//        std::cout << "Put will done" << std::endl;
        _currentSize = copySize;
        _currentSize += body->size();
        bool result = _insert(fileName, body, false);
        _printCache("put");
        _printCacheSizeSorted("put");
        _printDeleted("put");
        return result;
    }
    _recordForDelete.clear();
    return false;
}

//  ================================================

bool Cache::_deletedInsert(std::string &fileName, std::shared_ptr<Body>& body, deleted_map_iterator &deletedRecord) {
//    std::cout << "This record was deleted:" << fileName << std::endl;
    auto currentMinRate = _sortedCache.begin();
    bool swap = true;
    size_t copySize = _currentSize;

    while (copySize + body->size() > _cache_size) {
        if ((deletedRecord->second <= currentMinRate->second->second.last_rate) || (_cache.size() == _recordForDelete.size())) {
//            if (deletedRecord->second <= currentMinRate->second->second.last_rate)
//                std::cout << "No put: this record worse the worst record in cache" << std::endl;
//            else
//                std::cout << "No put: this record too big" << std::endl;
            swap = false;
            break;
        } else {
            _recordForDelete.push_back(currentMinRate->second);
            copySize -= currentMinRate->second->second.body->size();
            currentMinRate++;
        }
    }

    if (swap) {
//        std::cout << "Put will done" << std::endl;
        _currentSize = copySize;
        _currentSize += body->size();
        bool result = _insert(fileName, body, true);
        _printCache("put");
        _printCacheSizeSorted("put");
        _printDeleted("put");
        return result;
    }
    _recordForDelete.clear();
    return false;
}


bool Cache::_insert(std::string &fileName, std::shared_ptr<Body>& body, bool isDeleted) {
    for (auto it : _recordForDelete) {
        _deletedRecords.insert(std::pair<std::string, double>(it->first, it->second.last_rate));
        _sortedCache.erase(_sortedCache.begin());
        _cache.erase(it);
        std::cout << "[Cache] Deleted:" << it->first << " With rate:" << it->second.last_rate << std::endl;
    }
    _recordForDelete.clear();

    if (isDeleted) {
        double oldRate = _deletedRecords.find(fileName)->second;
        _deletedRecords.erase(fileName);

        auto newIter = _cache.emplace(std::pair<std::string, CacheRecord>(fileName, CacheRecord(body, oldRate, 1)));
        _sortedCache.emplace(std::pair<double, map_iterator>(oldRate, newIter.first));

        std::cout << "[Cache] Insert from deleted:" << fileName << " With rate:" << oldRate << std::endl;
    } else {
        auto newIter = _cache.emplace(std::pair<std::string, CacheRecord>(fileName, CacheRecord{body, LONG_MAX - 1, 1}));
        _sortedCache.emplace(std::pair<double, map_iterator>(LONG_MAX - 1, newIter.first));

        std::cout << "[Cache] Insert:" << fileName << " With rate:" << LONG_MAX - 1 << std::endl;
    }

    return true;
}

void Cache::_printCache(std::string location) {
//    std::cout << _cache_size << "--" << _currentSize << std::endl;
//    std::cout << "[" << location << "]" << "Cache:" << std::endl;
    //for (auto it : _cache) {
//        std::cout << it.first << ": " << it.second.last_rate << "->" << it.second.require_count << std::endl;
//    }
//    std::cout << std::endl;
}

void Cache::_printCacheSizeSorted(std::string location) {
//    std::cout << "[" << location << "]" << "Cache sorted:" << std::endl;
    for (auto it : _sortedCache) {
//        std::cout << it.first << ": " << it.second->first << "==" << it.second->second.last_rate << std::endl;
    }
//    std::cout << std::endl;
}

void Cache::_printDeleted(std::string location) {
//    std::cout << "[" << location << "]" << "Deleted:" << std::endl;
    for (auto it : _deletedRecords) {
//        std::cout << it.first << ": " << it.second << std::endl;
    }
//    std::cout << std::endl;
}

void Cache::_calculateRate() {
    auto end = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - _start);
    if (elapsed >= RATE_INTERVAL) {
        _start = std::chrono::steady_clock::now();
        for (auto it = _cache.begin(); it != _cache.end(); ++it) {
            _sortedCache.erase(it->second.last_rate);                                                    // Удалить из отсортированного контейнера
            std::cout << it->first << " REQUIRED: " << it->second.require_count << std::endl;
            it->second.last_rate = ((double)it->second.require_count / (double)elapsed.count());         // Обновить запросы за последний промежуток в основном контейнере
            it->second.require_count = 0;
            _sortedCache.emplace(std::pair<double, map_iterator>(it->second.last_rate, it));                       // Вставить обновленную версиию
        }
    }
}



CacheRecord::CacheRecord(std::shared_ptr<Body>& body, size_t l_r, size_t r_c) :
    body(body),
    last_rate(l_r),
    require_count(r_c)
{}

CacheRecord::CacheRecord(CacheRecord &&other) :
    body(std::move(other.body)),
    last_rate(other.last_rate),
    require_count(other.require_count)
{}

CacheRecord &CacheRecord::operator=(CacheRecord &&other) {
    body = (std::move(other.body));
    last_rate = (other.last_rate);
    require_count = (other.require_count);
    return *this;
}
