#include <string>
#include <vector>
#include <memory>

// define our hashing
size_t MurmurHash(const void * key, int len);

template <typename T>
inline size_t hash(const T& t) {
	return MurmurHash(&t, sizeof(T));
}

template <typename T>
inline size_t hash(const std::vector<T>& t) {
	return MurmurHash(t.data(), static_cast<int>(t.size() * sizeof(T)));
}

template <>
inline size_t hash(const size_t& t) {
	return t;
}

template <>
inline size_t hash(const std::string& t) {
	return MurmurHash(t.data(), static_cast<int>(t.size()));
}

// simplest hash table implementation I could think of
template<typename H, typename T>
class HashTable {
    // Tune for performance
    // lower values reduce memory footprint at the cost of write speed
    static constexpr size_t bucketGrowthRatio = 7;
    // higher values reduce memory footprint at the cost of read and write speed
    static constexpr size_t bucketSize = 1;

    size_t bucketCount = 16;

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
        bucketCount *= bucketGrowthRatio;
        auto new_buckets = new BucketList(bucketCount);
  
        for (auto& buck : *buckets) {
            for (auto& it : buck.items) {
                (*new_buckets)[getBucketIndex(it.hash)].items.push_back(it);
            }
        }

        buckets = BucketListPtr(new_buckets);
    }

public:
    HashTable() : buckets(BucketListPtr(new BucketList(bucketCount))) {}
    
    T& operator[](H indexer){
        size_t index = hash(indexer);
        bucket& buck = (*buckets)[getBucketIndex(index)];
        for (item& it : buck.items) {
            if (it.hash == index) {
                return it.value;
            }
        }
        
        if (buck.items.size() < bucketSize) {
            buck.items.push_back(item{index, T()});
            return buck.items.back().value;
        }

        rebalance();

        bucket& newbucket = (*buckets)[getBucketIndex(index)];
        newbucket.items.push_back(item{index, T()});
        return newbucket.items.back().value;
    }

    size_t bucket_count() {
        return bucketCount;
    }
};
