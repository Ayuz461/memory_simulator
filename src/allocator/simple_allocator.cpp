#include "phase1_simple_allocator.h"
#include <iostream>

Block::Block(size_t s, bool f, Block* n) 
    : size(s), is_free(f), next(n) {}

MemoryManager::MemoryManager(size_t size) {
    this->totalSize = size;
    this->memoryPool.resize(size);
    this->freeListHead = reinterpret_cast<Block*>(memoryPool.data());
    
    size_t initialSize = size - sizeof(Block);
    *freeListHead = Block(initialSize, true, nullptr);
}

void MemoryManager::dumpMemory() {
    Block* current = freeListHead;
    std::cout << "--- Memory Dump ---\n";
    while (current != nullptr) {
        std::cout << "Block at " << current << ": "
                  << (current->is_free ? "FREE" : "USED")
                  << " | Size: " << current->size << "\n";
        current = current->next;
    }
    std::cout << "-------------------\n";
}

void* MemoryManager::my_malloc(size_t size) {
    return nullptr; 
}

void MemoryManager::my_free(void* ptr) {
    if (ptr == nullptr) {
        return; 
    }

    Block* blockToFree = reinterpret_cast<Block*>(
        reinterpret_cast<char*>(ptr) - sizeof(Block)
    );

    blockToFree->is_free = true;

    if (blockToFree->next != nullptr && blockToFree->next->is_free) {
        blockToFree->size += sizeof(Block) + blockToFree->next->size;
        blockToFree->next = blockToFree->next->next;
    }

    Block* current = freeListHead;
    while (current != nullptr) {
        if (current->next == blockToFree) {
            if (current->is_free) {
                current->size += sizeof(Block) + blockToFree->size;
                current->next = blockToFree->next;
            }
            return;
        }
        current = current->next;
    }
}
