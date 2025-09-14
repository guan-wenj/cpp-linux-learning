//
// Created by guan on 2025/9/14.
//

#ifndef CPP_LINUX_LEARNING_LRU_H
#define CPP_LINUX_LEARNING_LRU_H

#include <list>
#include <ranges>
#include <unordered_map>
#include <stdexcept>


template<typename K,typename V>
class LRU_cache {
public:
    using KeyType=K;
    using ValueType=V;
    using PairType=std::pair<KeyType,ValueType>;
    using ListType=std::list<PairType>;
    using Iterator=ListType::iterator;
    using MapType=std::unordered_map<KeyType,Iterator>;
private:
    size_t capacity_;
    ListType data_list_;
    MapType key_map_;

    /*
     将节点移到头部
     */
    void move_to_front(Iterator it) {
        if (it != data_list_.begin()) {
            data_list_.splice(data_list_.begin(),data_list_,it);
        }
    }

    void evict_oldest(){
        if (data_list_.empty()) {
            throw std::runtime_error("LRU cache is empty");
        }
        KeyType oldest_key = data_list_.back().first;
        data_list_.pop_back();
        key_map_.erase(oldest_key);
    }
public:
    explicit LRU_cache(size_t capacity) :capacity_(capacity) {
        if (capacity <= 0) {
            throw std::runtime_error("LRU cache capacity must be > 0");
        }
    }

    LRU_cache(const LRU_cache&) = delete;
    LRU_cache& operator=(const LRU_cache&) = delete;

    LRU_cache(LRU_cache&&) = default;
    LRU_cache& operator=(LRU_cache&&) = default;

    ~LRU_cache() = default;

    ValueType get(const KeyType& key) {
        auto map_it = key_map_.find(key);
        if (map_it == key_map_.end()) {
            return ValueType();
        }
        Iterator it=map_it->second;
        move_to_front(it);
        return it->second;
    }

    void put(const KeyType& key, ValueType value) {
        auto map_it = key_map_.find(key);
        if (map_it != key_map_.end()) {
            Iterator list_it=map_it->second;
            list_it->second = value;
            move_to_front(list_it);
            return;
        }
        if (data_list_.size()>=capacity_) {
            evict_oldest();
        }
        data_list_.emplace_front(std::make_pair(key, value));
        key_map_[key]=data_list_.begin();
    }

    bool contains(const KeyType& key) const noexcept{
        return key_map_.find(key) != key_map_.end();
    }

    size_t size() const noexcept {
        return data_list_.size();
    }

    size_t capacity() const noexcept {
        return capacity_;
    }


    void clear() noexcept {
        data_list_.clear();
        key_map_.clear();
    }


};


#endif //CPP_LINUX_LEARNING_LRU_H