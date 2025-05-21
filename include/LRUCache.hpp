#ifndef LRU_CACHE_HPP
#define LRU_CACHE_HPP

#include <string>
#include <unordered_map>
#include <list>
#include <mutex>

using namespace std;

struct CacheEntry{
     list<string>::iterator it;
    string value;
    time_t expireAt;
};

class LRUCache {
    public:
        explicit LRUCache(size_t capacity);
        void set(const string& key , const string& value, int ttl);
        string get(const string& key);
        void remove(const string& key);

private:
    size_t capacity_;
    unordered_map<string, CacheEntry> cache_;
    list<string> lruList_; // List to maintain the order of usage
    mutex mtx_; // Mutex for thread safety
};


#endif