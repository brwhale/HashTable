#pragma once

#include <string>
#include <vector>
#include <memory>
#include <functional>

// simplest hash table implementation I could think of
template<typename K, typename T, typename H = std::hash<K>>
class HashTable {
    // Tune for performance
    static constexpr size_t bucketGrowthRatio = 5;
    static constexpr size_t bucketSize = 3;
    static constexpr double minimumFillBeforeRebalance = .95;
    size_t itemCount = 0;
    size_t bucketCount = 4;
    size_t usedBucketCount = 0;
    double inverseBucketCount = 1/static_cast<double>(bucketCount);

    size_t getBucketIndex(size_t hash) {
        return hash % bucketCount;
    }

    struct item {
        size_t hash;
        T value;
    };

    struct bucket {
        std::vector<item> items;
        bucket() {
            items.reserve(bucketSize);
        }
    };

    using BucketList = std::vector<bucket>;
    using BucketListPtr = std::unique_ptr<BucketList>;

    BucketListPtr buckets;

    void rebalance() {
        usedBucketCount = 0;
        bucketCount *= bucketGrowthRatio;
        inverseBucketCount = 1/static_cast<double>(bucketCount);
        auto new_buckets = new BucketList(bucketCount);
  
        for (auto& buck : *buckets) {
            for (auto& it : buck.items) {
                auto& its = (*new_buckets)[getBucketIndex(it.hash)].items;
                if (its.size() == 0) {
                    ++usedBucketCount;
                }
                its.push_back(it);
            }
        }

        buckets = BucketListPtr(new_buckets);
    }

public:
    HashTable() : buckets(BucketListPtr(new BucketList(bucketCount))) {}
    
    T& operator[](K indexer){
        size_t index = H{}(indexer);
        bucket& buck = (*buckets)[getBucketIndex(index)];
        for (item& it : buck.items) {
            if (it.hash == index) {
                return it.value;
            }
        }
        
        if (buck.items.size() < bucketSize || 
            (usedBucketCount * inverseBucketCount) < minimumFillBeforeRebalance ) {
            ++itemCount;
            if (buck.items.size() == 0){
                ++usedBucketCount;
            }
            buck.items.push_back(item{index, T()});
            return buck.items.back().value;
        }

        rebalance();

        bucket& newbucket = (*buckets)[getBucketIndex(index)];
        ++itemCount;
        if (newbucket.items.size() == 0){
            ++usedBucketCount;
        }
        newbucket.items.push_back(item{index, T()});
        return newbucket.items.back().value;
    }

    size_t bucket_count() {
        return bucketCount;
    }
};
