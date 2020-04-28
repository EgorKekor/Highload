//
// Created by kekor on 20.04.2020.
//

#ifndef HIGHLOAD_CACHE_H
#define HIGHLOAD_CACHE_H

#include <map>
#include <memory>
#include <chrono>
#include <vector>
#include "../include/config.h"

struct CacheRecord {
    std::shared_ptr<std::string> s_ptr;
    size_t last_rate;
    size_t require_count;
};

class Cache {
public:
    typedef std::map<std::string, CacheRecord> map_type;
    typedef std::map<std::string, CacheRecord>::iterator map_iterator;
    typedef std::map<std::string, size_t>::iterator deleted_map_iterator;
    Cache(size_t sz = MAX_CACHE_SIZE);

    std::shared_ptr<std::string> get(std::string fileName);
    bool put(std::string fileName, std::shared_ptr<std::string> sPtr);
private:
    std::map<std::string, CacheRecord> _cache;
    std::multimap<size_t, map_iterator> _sortedCache;
    std::map<std::string, size_t> _deletedRecords;
    std::vector<map_iterator> _recordForDelete;
    std::chrono::time_point<std::chrono::steady_clock> _start;
    size_t _currentSize = 0;
    size_t _cache_size;

    bool _regularInsert(std::string &fileName, std::shared_ptr<std::string> &sPtr);
    bool _deletedInsert(std::string &fileName, std::shared_ptr<std::string> &sPtr, deleted_map_iterator &delRec);
    bool _insert(std::string &fileName, std::shared_ptr<std::string> &sPtr, bool isDeleted);
    void _calculateRate();

    void _printCache(std::string location);
    void _printCacheSizeSorted(std::string location);
    void _printDeleted(std::string location);
};

#endif //HIGHLOAD_CACHE_H
