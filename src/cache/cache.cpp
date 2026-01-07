#include "../../include/cache.h"
#include <iostream>
#include <climits>

using namespace std;

// Global timer for LRU
int global_time = 0;

Cache::Cache(int S_num_sets, int E_associativity_in, int B_block_size) {
    E_associativity = E_associativity_in;
    b_offset_bits = 0;
    while ((1 << b_offset_bits) < B_block_size) b_offset_bits++;
    
    s_index_bits = 0;
    while ((1 << s_index_bits) < S_num_sets) s_index_bits++;

    sets.resize(S_num_sets, vector<CacheLine>(E_associativity));
}

void access_cache(Cache &cache, unsigned long address, bool is_write) {
    global_time++;

    unsigned long set_index_mask = (1 << cache.s_index_bits) - 1;
    unsigned long set_index = (address >> cache.b_offset_bits) & set_index_mask;
    unsigned long tag = address >> (cache.b_offset_bits + cache.s_index_bits);

    vector<CacheLine> &current_set = cache.sets[set_index];
    bool hit = false;

    for (int i = 0; i < cache.E_associativity; i++) {
        if (current_set[i].valid && current_set[i].tag == tag) {
            hit = true;
            cache.hits++;
            current_set[i].lru_counter = global_time;
            if (is_write) current_set[i].dirty = true;
            break;
        }
    }

    if (!hit) {
        cache.misses++;
        int lru_index = 0;
        int min_time = INT_MAX;
        bool found_empty = false;

        for (int i = 0; i < cache.E_associativity; i++) {
            if (!current_set[i].valid) {
                lru_index = i;
                found_empty = true;
                break;
            }
            if (current_set[i].lru_counter < min_time) {
                min_time = current_set[i].lru_counter;
                lru_index = i;
            }
        }

        if (!found_empty) {
            cache.evictions++;
        }

        current_set[lru_index].valid = true;
        current_set[lru_index].tag = tag;
        current_set[lru_index].lru_counter = global_time;
        current_set[lru_index].dirty = is_write;
    }
}