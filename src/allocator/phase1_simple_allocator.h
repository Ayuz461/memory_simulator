#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H

#include <vector>
#include <cstddef>

struct Block {
    size_t size;
    bool is_free;
    Block* next;
    
    Block(size_t s, bool f = true, Block* n = nullptr);
};

class MemoryManager {
private:
    std::vector<char> memoryPool;
    Block* freeListHead;
    size_t totalSize;

public:
    MemoryManager(size_t size);
    void* my_malloc(size_t size);
    void my_free(void* ptr);
    void dumpMemory();
};

#endif