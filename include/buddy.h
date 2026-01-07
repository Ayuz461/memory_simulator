#ifndef BUDDY_H
#define BUDDY_H

#include <vector>

struct Block {
    int size;
    bool is_free;
    int offset;
};

class BuddyAllocator {
    int total_memory_size;
    std::vector<Block> memory_map;

public:
    BuddyAllocator(int size);
    void allocate(int request_size);
    void deallocate(int offset);
    void print_memory();
};

#endif