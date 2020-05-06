//
// Created by kekos on 07.04.2020.
//

#ifndef HIGHLOAD_BLOCKMAP_HPP
#define HIGHLOAD_BLOCKMAP_HPP

#include <iostream>
#include <map>
#include <condition_variable>


template <class VALUE_TYPE, class FRIEND_KEY, class FRIEND_VAL>
class BlockIterator;


template <class KEY, class T>
class BlockMap {
    typedef std::pair<KEY, T> value_type;
    typedef typename std::map<KEY, T>::iterator base_iterator;
    typedef BlockIterator<base_iterator, KEY, T> iterator;
    typedef BlockIterator<base_iterator, KEY, T> const_iterator;
    friend class BlockIterator<base_iterator, KEY, T>;
public:
    BlockMap() { _saveAss = std::shared_ptr<BlockMap<KEY, T>>(this); };
    T& operator[]( const KEY& key ) { return _map[key]; };
    T& operator[]( KEY&& key ) { return _map[std::move(key)]; };
    T& at( const KEY& key ) { return _map.at(key); };
    const T & at( const KEY& key ) const { return _map.at(key); };

    std::pair<base_iterator, bool> insert( const value_type& value ) {
        _operation.lock();
        auto orig = _map.insert(value);
        _operation.unlock();
        return orig;


//        auto iterShared = std::make_shared<base_iterator>(orig.first);
//        return  std::pair<iterator, bool>(iterator(iterShared, _saveAss), orig.second);
    };

    base_iterator find(const KEY& key) {
        _operation.lock();
        KEY& ret = _map.find(key);
        _operation.unlock();
        return ret;
    };

    size_t erase( const KEY& key ) {
        _operation.lock();
        size_t ret = _map.erase(key);
        _operation.unlock();
        return ret;
    };


    iterator begin() { return iterator(std::make_shared<base_iterator>(_map.begin()), _saveAss); };
//    iterator end() { return iterator(std::make_shared<base_iterator>(_map.end()), _saveAss); };
    base_iterator end() { return _map.end(); };
    const_iterator begin() const { return const_iterator(std::make_shared<base_iterator>(_map.begin()), _saveAss); };
    const_iterator end() const { return Bconst_iterator(std::make_shared<base_iterator>(_map.end()), _saveAss); };
private:
    std::shared_ptr<BlockMap<KEY, T>> _saveAss;
    bool _blocked = false;
    std::map<KEY, T> _map;
    std::condition_variable_any _haveData;
    std::mutex _haveDataMutex;
    std::mutex _operation;
};



template <class T, class KEY, class VAL>
class BlockIterator : public std::iterator<std::input_iterator_tag, T> {
public:
    friend class BlockMap<KEY, VAL>;
    BlockIterator<T, KEY, VAL>(std::shared_ptr<T> iter, std::shared_ptr<BlockMap<KEY, VAL>> blockMap) : _iter(iter), _blockMap(blockMap) {

    };
    BlockIterator<T, KEY, VAL>(const BlockIterator<T, KEY, VAL> &it) : _iter(it._iter), _blockMap(it._blockMap) {};

    bool operator!=(BlockIterator<T, KEY, VAL> const& other) const { return **_iter != **other; };
    bool operator==(BlockIterator<T, KEY, VAL> const& other) const { return **_iter == **other; };
    std::pair<KEY, VAL> operator*() const { return **_iter; };
    BlockIterator<T, KEY, VAL>& operator++() {
        if (*_iter == _blockMap->_map.end()) {
            _blockMap->_blocked = true;
            _blockMap->_haveDataMutex.lock();
            _blockMap->_haveData.wait(_blockMap->_haveDataMutex);
            _blockMap->_blocked = false;
            _blockMap->_haveDataMutex.unlock();

            _iter = std::make_shared<T>(_blockMap->_map.begin());
        }
        (*_iter)++;
        return *this;
    };
private:
    std::shared_ptr<BlockMap<KEY, VAL>> _blockMap;
    std::shared_ptr<T> _iter;
};

#endif //HIGHLOAD_BLOCKMAP_HPP
