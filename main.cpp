#include <chrono>
#include <vector>
#include <map>
#include <unordered_map>
#include <stdlib.h>
#include <iostream>

#include "HashTable.hpp"

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

    std::vector<int> values(100000, 0);
    std::vector<std::string> valueStrings;
    valueStrings.reserve(values.size());
    std::map<size_t, size_t> mmap;
    std::unordered_map<size_t, size_t> umap;
    HashTable<size_t, size_t> cmap;
    std::map<std::string, size_t> mmap_string;
    std::unordered_map<std::string, size_t> umap_string;
    HashTable<std::string, size_t> cmap_string;
    
    // generate values
    auto startTime = GetTimeStamp();
    for (auto& val : values) {
        val = rand() & 100000;
    }
    auto EndTime = GetTimeStamp();
    std::cout << "time to fill vector:\t\t\t\t\t" << GetSeconds(startTime, EndTime) << "\n";

    startTime = GetTimeStamp();
    for (auto val : values) {
        valueStrings.push_back(std::to_string(val));
    }
    EndTime = GetTimeStamp();
    std::cout << "time to fill string vector:\t\t\t\t" << GetSeconds(startTime, EndTime) << "\n";

    startTime = GetTimeStamp();
    for (size_t i = 0; i < values.size(); ++i) {
        mmap[i] = values[i];
    }
    EndTime = GetTimeStamp();
    std::cout << "time to fill std map:\t\t\t\t\t" << GetSeconds(startTime, EndTime) << "\n";

    startTime = GetTimeStamp();
    for (size_t i = 0; i < values.size(); ++i) {
        umap[i] = values[i];
    }
    EndTime = GetTimeStamp();
    std::cout << "time to fill std unordered map:\t\t\t\t" << GetSeconds(startTime, EndTime) << "\n";

    startTime = GetTimeStamp();
    for (size_t i = 0; i < values.size(); ++i) {
        cmap[i] = values[i];
    }
    EndTime = GetTimeStamp();
    std::cout << "time to fill custom map:\t\t\t\t" << GetSeconds(startTime, EndTime) << "\n";

    startTime = GetTimeStamp();
    for (size_t i = 0; i < values.size(); ++i) {
        mmap_string[valueStrings[i]] = values[i];
    }
    EndTime = GetTimeStamp();
    std::cout << "time to fill std string map:\t\t\t\t" << GetSeconds(startTime, EndTime) << "\n";

    startTime = GetTimeStamp();
    for (size_t i = 0; i < values.size(); ++i) {
        umap_string[valueStrings[i]] = values[i];
    }
    EndTime = GetTimeStamp();
    std::cout << "time to fill std unordered string map:\t\t\t" << GetSeconds(startTime, EndTime) << "\n";

    startTime = GetTimeStamp();
    for (size_t i = 0; i < values.size(); ++i) {
        cmap_string[valueStrings[i]] = values[i];
    }
    EndTime = GetTimeStamp();
    std::cout << "time to fill custom string map:\t\t\t\t" << GetSeconds(startTime, EndTime) << "\n\n";

    size_t vecSum = 0;
    startTime = GetTimeStamp();
    for (size_t i = 0; i < values.size(); ++i) {
        vecSum += values[i];
    }
    EndTime = GetTimeStamp();
    std::cout << "time to sum (" << vecSum << ") vec:\t\t\t\t" << GetSeconds(startTime, EndTime) << "\n";

    size_t mmapSum = 0;
    startTime = GetTimeStamp();
    for (size_t i = 0; i < values.size(); ++i) {
        mmapSum += mmap[i];
    }
    EndTime = GetTimeStamp();
    std::cout << "time to sum (" << mmapSum << ") std map:\t\t\t" << GetSeconds(startTime, EndTime) << "\n";

    size_t mapSum = 0;
    startTime = GetTimeStamp();
    for (size_t i = 0; i < values.size(); ++i) {
        mapSum += umap[i];
    }
    EndTime = GetTimeStamp();
    std::cout << "time to sum (" << mapSum << ") std unordered map:\t\t" << GetSeconds(startTime, EndTime) << " with " << umap.bucket_count() << " buckets\n";

    size_t cmapSum = 0;
    startTime = GetTimeStamp();
    for (size_t i = 0; i < values.size(); ++i) {
        cmapSum += cmap[i];
    }
    EndTime = GetTimeStamp();
    std::cout << "time to sum (" << cmapSum << ") custom map:\t\t\t" << GetSeconds(startTime, EndTime) << " with " << cmap.bucket_count() << " buckets\n\n";

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
    std::cout << "time to sum (" << cmapSum << ") custom string key map:\t\t" << GetSeconds(startTime, EndTime) << " with " << cmap_string.bucket_count() << " buckets\n";

    return 0;
}

// this all comes from the public domain murmurhash on github
// https://github.com/aappleby/smhasher/

#if defined(_MSC_VER)

#define FORCE_INLINE	__forceinline

#include <stdlib.h>

#define ROTL32(x,y)	_rotl(x,y)
#define ROTL64(x,y)	_rotl64(x,y)

#define BIG_CONSTANT(x) (x)

// Other compilers

#else	// defined(_MSC_VER)

#define	FORCE_INLINE inline __attribute__((always_inline))

inline uint32_t rotl32(uint32_t x, int8_t r)
{
	return (x << r) | (x >> (32 - r));
}

inline uint64_t rotl64(uint64_t x, int8_t r)
{
	return (x << r) | (x >> (64 - r));
}

#define	ROTL32(x,y)	rotl32(x,y)
#define ROTL64(x,y)	rotl64(x,y)

#define BIG_CONSTANT(x) (x##LLU)

#endif // !defined(_MSC_VER)

//-----------------------------------------------------------------------------
// Block read - if your platform needs to do endian-swapping or can only
// handle aligned reads, do the conversion here

FORCE_INLINE uint32_t getblock32(const uint32_t * p, int i)
{
	return p[i];
}

FORCE_INLINE uint64_t getblock64(const uint64_t * p, int i)
{
	return p[i];
}

//-----------------------------------------------------------------------------
// Finalization mix - force all bits of a hash block to avalanche

FORCE_INLINE uint64_t fmix64(uint64_t k)
{
	k ^= k >> 33;
	k *= BIG_CONSTANT(0xff51afd7ed558ccd);
	k ^= k >> 33;
	k *= BIG_CONSTANT(0xc4ceb9fe1a85ec53);
	k ^= k >> 33;

	return k;
}

size_t MurmurHash(const void * key, int len) {
	uint32_t seed = 2384789;
	const uint8_t * data = (const uint8_t*)key;
	const int nblocks = len / 16;

	uint64_t h1 = seed;
	uint64_t h2 = seed;

	const uint64_t c1 = BIG_CONSTANT(0x87c37b91114253d5);
	const uint64_t c2 = BIG_CONSTANT(0x4cf5ad432745937f);

	//----------
	// body

	const uint64_t * blocks = (const uint64_t *)(data);

	for (int i = 0; i < nblocks; i++)
	{
		uint64_t k1 = getblock64(blocks, i * 2 + 0);
		uint64_t k2 = getblock64(blocks, i * 2 + 1);

		k1 *= c1; k1 = ROTL64(k1, 31); k1 *= c2; h1 ^= k1;

		h1 = ROTL64(h1, 27); h1 += h2; h1 = h1 * 5 + 0x52dce729;

		k2 *= c2; k2 = ROTL64(k2, 33); k2 *= c1; h2 ^= k2;

		h2 = ROTL64(h2, 31); h2 += h1; h2 = h2 * 5 + 0x38495ab5;
	}

	//----------
	// tail

	const uint8_t * tail = (const uint8_t*)(data + nblocks * 16);

	uint64_t k1 = 0;
	uint64_t k2 = 0;

	switch (len & 15)
	{
	case 15: k2 ^= ((uint64_t)tail[14]) << 48;
	case 14: k2 ^= ((uint64_t)tail[13]) << 40;
	case 13: k2 ^= ((uint64_t)tail[12]) << 32;
	case 12: k2 ^= ((uint64_t)tail[11]) << 24;
	case 11: k2 ^= ((uint64_t)tail[10]) << 16;
	case 10: k2 ^= ((uint64_t)tail[9]) << 8;
	case  9: k2 ^= ((uint64_t)tail[8]) << 0;
		k2 *= c2; k2 = ROTL64(k2, 33); k2 *= c1; h2 ^= k2;

	case  8: k1 ^= ((uint64_t)tail[7]) << 56;
	case  7: k1 ^= ((uint64_t)tail[6]) << 48;
	case  6: k1 ^= ((uint64_t)tail[5]) << 40;
	case  5: k1 ^= ((uint64_t)tail[4]) << 32;
	case  4: k1 ^= ((uint64_t)tail[3]) << 24;
	case  3: k1 ^= ((uint64_t)tail[2]) << 16;
	case  2: k1 ^= ((uint64_t)tail[1]) << 8;
	case  1: k1 ^= ((uint64_t)tail[0]) << 0;
		k1 *= c1; k1 = ROTL64(k1, 31); k1 *= c2; h1 ^= k1;
	};

	//----------
	// finalization

	h1 ^= len; h2 ^= len;

	h1 += h2;
	h2 += h1;

	h1 = fmix64(h1);
	h2 = fmix64(h2);

	h1 += h2;
	h2 += h1;

	// just xor the two halves together
	// the bits should be avalanched enough to work
	return h1 ^ h2;
}
