#ifndef CACHE_H
#define CACHE_H

#include <vector>

struct CacheLine {
    bool valid = false;
    bool dirty = false;
    unsigned long tag = 0;
    int lru_counter = 0;
};

class Cache {
public:
    int s_index_bits;
    int b_offset_bits;
    int E_associativity;
    std::vector<std::vector<CacheLine>> sets;
    
    int hits = 0;
    int misses = 0;
    int evictions = 0;

    Cache(int S_num_sets, int E_associativity_in, int B_block_size);
};

void access_cache(Cache &cache, unsigned long address, bool is_write);

#endif