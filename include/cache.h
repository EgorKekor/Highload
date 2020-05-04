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
#include "../include/response.h"

struct CacheRecord {
    CacheRecord(std::shared_ptr<Body>& body, size_t l_r, size_t r_c);

    CacheRecord(CacheRecord &&other);
    CacheRecord& operator=(CacheRecord &&other);

    std::shared_ptr<Body> body;
    double last_rate;
    size_t require_count;
};

struct DeletedRecord {
    double last_rate;
    size_t require_count;
};

class Cache {
public:
    typedef std::map<std::string, CacheRecord> map_type;
    typedef std::map<std::string, CacheRecord>::iterator map_iterator;
    typedef std::map<std::string, DeletedRecord>::iterator deleted_map_iterator;
    Cache(size_t sz = MAX_CACHE_SIZE);

    std::shared_ptr<Body> get(std::string &fileName);
    bool put(std::string &fileName, std::shared_ptr<Body>& body);
private:
    std::shared_ptr<Body> _fake;

    std::map<std::string, CacheRecord> _cache;
    std::multimap<double, map_iterator> _sortedCache;   // Частота запросов - указатель на оригинал
    std::map<std::string, DeletedRecord> _deletedRecords;      // Имя файла - частота запросов
    std::vector<map_iterator> _recordForDelete;
    std::chrono::time_point<std::chrono::steady_clock> _start;
    size_t _currentSize = 0;
    size_t _cache_size;

    bool _regularInsert(std::string &fileName, std::shared_ptr<Body>& body);
    bool _deletedInsert(std::string &fileName, std::shared_ptr<Body>& body, deleted_map_iterator &delRec);
    bool _insert(std::string &fileName, std::shared_ptr<Body>& body, bool isDeleted);
    void _calculateRate();

    void _printCache(std::string location);
    void _printCacheSizeSorted(std::string location);
    void _printDeleted(std::string location);
};

#endif //HIGHLOAD_CACHE_H
