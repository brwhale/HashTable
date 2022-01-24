#include <chrono>
#include <vector>
#include <map>
#include <unordered_map>
#include <stdlib.h>
#include <iostream>

#include "HashTable.hpp"
#include "Murmurhash.hpp"

using duration = std::chrono::duration<double>;
using Clock = std::chrono::high_resolution_clock;
using timePoint = Clock::time_point;

timePoint GetTimeStamp() {
    return Clock::now();
}

double GetSeconds(timePoint A, timePoint B) {
    duration d = B-A;
	return d.count();
}

int main() {
    // set consistent random seed
    srand(10);

    // disbale scientific notation
    std::cout << std::fixed;

    std::vector<int> values(1000000, 0);
    std::vector<std::string> valueStrings;
    valueStrings.reserve(values.size());
    std::map<size_t, size_t> mmap;
    std::unordered_map<size_t, size_t> umap;
    HashTable<size_t, size_t> cmap;
    HashTable<size_t, size_t, MurmurHashHasher> cmap_murmur;
    std::map<std::string, size_t> mmap_string;
    std::unordered_map<std::string, size_t> umap_string;
    HashTable<std::string, size_t> cmap_string;
    HashTable<std::string, size_t, MurmurHashHasher> cmap_string_murmur;
    
    // generate values
    auto startTime = GetTimeStamp();
    for (auto& val : values) {
        val = rand();
    }
    auto EndTime = GetTimeStamp();
    std::cout << "time to fill vector:\t\t\t\t\t" << GetSeconds(startTime, EndTime) << "\n";

    startTime = GetTimeStamp();
    for (size_t i = 0; i < values.size(); ++i) {
        mmap[values[i]] = i;
    }
    EndTime = GetTimeStamp();
    std::cout << "time to fill std map:\t\t\t\t\t" << GetSeconds(startTime, EndTime) << "\n";

    startTime = GetTimeStamp();
    for (size_t i = 0; i < values.size(); ++i) {
        umap[values[i]] = i;
    }
    EndTime = GetTimeStamp();
    std::cout << "time to fill std unordered map:\t\t\t\t" << GetSeconds(startTime, EndTime) << "\n";

    startTime = GetTimeStamp();
    for (size_t i = 0; i < values.size(); ++i) {
        cmap[values[i]] = i;
    }
    EndTime = GetTimeStamp();
    std::cout << "time to fill hashtable:\t\t\t\t\t" << GetSeconds(startTime, EndTime) << "\n";

    startTime = GetTimeStamp();
    for (size_t i = 0; i < values.size(); ++i) {
        cmap_murmur[values[i]] = i;
    }
    EndTime = GetTimeStamp();
    std::cout << "time to fill hashtable (mhash):\t\t\t\t" << GetSeconds(startTime, EndTime) << "\n\n";



    startTime = GetTimeStamp();
    for (auto val : values) {
        valueStrings.push_back(std::to_string(val));
    }
    EndTime = GetTimeStamp();
    std::cout << "time to fill string vector:\t\t\t\t" << GetSeconds(startTime, EndTime) << "\n";

    startTime = GetTimeStamp();
    for (size_t i = 0; i < values.size(); ++i) {
        mmap_string[valueStrings[i]] = i;
    }
    EndTime = GetTimeStamp();
    std::cout << "time to fill std string map:\t\t\t\t" << GetSeconds(startTime, EndTime) << "\n";

    startTime = GetTimeStamp();
    for (size_t i = 0; i < values.size(); ++i) {
        umap_string[valueStrings[i]] = i;
    }
    EndTime = GetTimeStamp();
    std::cout << "time to fill std unordered string map:\t\t\t" << GetSeconds(startTime, EndTime) << "\n";

    startTime = GetTimeStamp();
    for (size_t i = 0; i < values.size(); ++i) {
        cmap_string[valueStrings[i]] = i;
    }
    EndTime = GetTimeStamp();
    std::cout << "time to fill string hashtable:\t\t\t\t" << GetSeconds(startTime, EndTime) << "\n";

    startTime = GetTimeStamp();
    for (size_t i = 0; i < values.size(); ++i) {
        cmap_string_murmur[valueStrings[i]] = i;
    }
    EndTime = GetTimeStamp();
    std::cout << "time to fill string hashtable (mhash):\t\t\t" << GetSeconds(startTime, EndTime) << "\n\n";



    size_t vecSum = 0;
    startTime = GetTimeStamp();
    for (size_t i = 0; i < values.size(); ++i) {
        vecSum += values[i];
    }
    EndTime = GetTimeStamp();
    std::cout << "time to sum (" << vecSum << ") vec:\t\t\t" << GetSeconds(startTime, EndTime) << "\n";

    size_t mmapSum = 0;
    startTime = GetTimeStamp();
    for (size_t i = 0; i < values.size(); ++i) {
        mmapSum += mmap[values[i]];
    }
    EndTime = GetTimeStamp();
    std::cout << "time to sum (" << mmapSum << ") std map:\t\t\t" << GetSeconds(startTime, EndTime) << "\n";

    size_t mapSum = 0;
    startTime = GetTimeStamp();
    for (size_t i = 0; i < values.size(); ++i) {
        mapSum += umap[values[i]];
    }
    EndTime = GetTimeStamp();
    std::cout << "time to sum (" << mapSum << ") std unordered map:\t\t" << GetSeconds(startTime, EndTime) << " with " << umap.bucket_count() << " buckets\n";

    size_t cmapSum = 0;
    startTime = GetTimeStamp();
    for (size_t i = 0; i < values.size(); ++i) {
        cmapSum += cmap[values[i]];
    }
    EndTime = GetTimeStamp();
    std::cout << "time to sum (" << cmapSum << ") hashtable:\t\t\t" << GetSeconds(startTime, EndTime) << " with " << cmap.bucket_count() << " buckets\n";

    cmapSum = 0;
    startTime = GetTimeStamp();
    for (size_t i = 0; i < values.size(); ++i) {
        cmapSum += cmap_murmur[values[i]];
    }
    EndTime = GetTimeStamp();
    std::cout << "time to sum (" << cmapSum << ") hashtable (mhash):\t\t" << GetSeconds(startTime, EndTime) << " with " << cmap_murmur.bucket_count() << " buckets\n\n";



    vecSum = 0;
    startTime = GetTimeStamp();
    for (size_t i = 0; i < valueStrings.size(); ++i) {
        vecSum += valueStrings[i].size();
    }
    EndTime = GetTimeStamp();
    std::cout << "time to sum lengths (" << vecSum << ") vec:\t\t\t" << GetSeconds(startTime, EndTime) << "\n";

    mmapSum = 0;
    startTime = GetTimeStamp();
    for (size_t i = 0; i < values.size(); ++i) {
        mmapSum += mmap_string[valueStrings[i]];
    }
    EndTime = GetTimeStamp();
    std::cout << "time to sum (" << mmapSum << ") std string map:\t\t" << GetSeconds(startTime, EndTime) << "\n";

    mapSum = 0;
    startTime = GetTimeStamp();
    for (size_t i = 0; i < values.size(); ++i) {
        mapSum += umap_string[valueStrings[i]];
    }
    EndTime = GetTimeStamp();
    std::cout << "time to sum (" << mapSum << ") std unordered string map:\t" << GetSeconds(startTime, EndTime) << " with " << umap_string.bucket_count() << " buckets\n";

    cmapSum = 0;
    startTime = GetTimeStamp();
    for (size_t i = 0; i < values.size(); ++i) {
        cmapSum += cmap_string[valueStrings[i]];
    }
    EndTime = GetTimeStamp();
    std::cout << "time to sum (" << cmapSum << ") string hashtable:\t\t" << GetSeconds(startTime, EndTime) << " with " << cmap_string.bucket_count() << " buckets\n";

    cmapSum = 0;
    startTime = GetTimeStamp();
    for (size_t i = 0; i < values.size(); ++i) {
        cmapSum += cmap_string_murmur[valueStrings[i]];
    }
    EndTime = GetTimeStamp();
    std::cout << "time to sum (" << cmapSum << ") string hashtable (mhash):\t" << GetSeconds(startTime, EndTime) << " with " << cmap_string_murmur.bucket_count() << " buckets\n\n";

    return 0;
}
