#include "../include/LRUCache.hpp"
#include <iostream>
#include <chrono>

using namespace std;

LRUCache::LRUCache(size_t capacity) : capacity_(capacity) {}

void LRUCache::set(const string& key , const string& value, int ttl){
    lock_guard<mutex> lock(mtx_);
    time_t now = time(nullptr);
    
    if(cache_.count(key)){
        lruList_.erase(cache_[key].it);

    }else if(cache_.size() >= capacity_){
        string oldKey = lruList_.back();
        lruList_.pop_back();
        cache_.erase(oldKey);
    }
    lruList_.push_front(key);
    cache_[key] = {lruList_.begin(), 
    value, now + ttl};
}

string LRUCache::get(const string& key){
    lock_guard<mutex> lock(mtx_);
    if(!cache_.count(key)){
        return "NOT FOUND";
    }
    time_t now = time(nullptr);
    auto &entry = cache_[key];
    if(entry.expireAt < now){
        lruList_.erase(cache_[key].it);
        cache_.erase(key);
        return "NOT FOUND";
    }
    lruList_.erase(cache_[key].it);
    lruList_.push_front(key);
    cache_[key].it = lruList_.begin();
    return entry.value;
}
void LRUCache::remove(const string& key){
    lock_guard<mutex> lock(mtx_);
    if(cache_.count(key)){
        lruList_.erase(cache_[key].it);
        cache_.erase(key);
    }
}