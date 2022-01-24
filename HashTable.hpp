#pragma once

#include <string>
#include <array>
#include <memory>
#include <functional>

// simplest hash table implementation I could think of
template<typename K, typename T, typename H = std::hash<K>>
class HashTable {
    // Tune for performance
    static constexpr size_t bucketGrowthRatio = 4; // must be pow of 2
    static constexpr size_t bucketSize = 16;
    size_t itemCount = 0;
    size_t bucketCount = 8;

    size_t getBucketIndex(size_t hash) {
        return hash & (bucketCount-1);
    }

    struct item {
        size_t hash;
        T value;
    };

    class bucket {
        std::array<item, bucketSize> items;
        int count = 0;
    public:
        void push_back(const item& it) {
            items[count] = it;
            ++count;
        }
        int size() {
            return count;
        }
        item* begin() {
            return &items[0];
        }
        item* end() {
            return &items[count];
        }
        item& back() {
            return items[count-1];
        }
    };

    using BucketList = std::vector<bucket>;
    using BucketListPtr = std::unique_ptr<BucketList>;

    BucketListPtr buckets;

    void rebalance() {
        bucketCount *= bucketGrowthRatio;
        auto new_buckets = new BucketList(bucketCount);
  
        for (auto& buck : *buckets) {
            for (auto& it : buck) {
                auto& its = (*new_buckets)[getBucketIndex(it.hash)];
                its.push_back(it);
            }
        }

        buckets = BucketListPtr(new_buckets);
    }

public:
    HashTable() : buckets(BucketListPtr(new BucketList(bucketCount))) {}
    
    T& operator[](K indexer){
        size_t index = H{}(indexer);
        bucket* buck = &(*buckets)[getBucketIndex(index)];
        for (item& it : *buck) {
            if (it.hash == index) {
                return it.value;
            }
        }
        
        while(1) {
            if (buck->size() < bucketSize) {
                ++itemCount;
                buck->push_back(item{index, T()});
                return buck->back().value;
            } else {
                rebalance();
                buck = &(*buckets)[getBucketIndex(index)];
            }
        }
    }

    size_t bucket_count() {
        return bucketCount;
    }

    void clear() {
        buckets->clear();
    }
};
