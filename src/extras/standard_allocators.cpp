#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <iomanip>

using namespace std;

// A simple memory block structure
struct Block {
    int id;
    size_t size;
    bool is_free;
};

class StandardAllocator {
    size_t total_memory;
    list<Block> memory;
    int next_id = 1;

public:
    StandardAllocator(size_t size) : total_memory(size) {
        // Initialize with one large free block
        memory.push_back({0, size, true});
    }

    // 1. FIRST FIT Strategy
    // Finds the FIRST free block that fits
    void allocateFirstFit(size_t size) {
        cout << "[First Fit] Requesting " << size << " bytes... ";
        for (auto it = memory.begin(); it != memory.end(); ++it) {
            if (it->is_free && it->size >= size) {
                splitBlock(it, size);
                return;
            }
        }
        cout << "Failed (No suitable block found)." << endl;
    }

    // 2. BEST FIT Strategy
    // Finds the SMALLEST free block that fits
    void allocateBestFit(size_t size) {
        cout << "[Best Fit] Requesting " << size << " bytes... ";
        auto best_it = memory.end();
        size_t smallest_diff = -1; // Max value

        for (auto it = memory.begin(); it != memory.end(); ++it) {
            if (it->is_free && it->size >= size) {
                size_t diff = it->size - size;
                if (diff < smallest_diff) {
                    smallest_diff = diff;
                    best_it = it;
                }
            }
        }

        if (best_it != memory.end()) {
            splitBlock(best_it, size);
        } else {
            cout << "Failed (No suitable block found)." << endl;
        }
    }

    // 3. WORST FIT Strategy
    // Finds the LARGEST free block
    void allocateWorstFit(size_t size) {
        cout << "[Worst Fit] Requesting " << size << " bytes... ";
        auto worst_it = memory.end();
        size_t largest_size = 0;

        for (auto it = memory.begin(); it != memory.end(); ++it) {
            if (it->is_free && it->size >= size) {
                if (it->size > largest_size) {
                    largest_size = it->size;
                    worst_it = it;
                }
            }
        }

        if (worst_it != memory.end()) {
            splitBlock(worst_it, size);
        } else {
            cout << "Failed (No suitable block found)." << endl;
        }
    }

    // Helper to handle splitting logic
    void splitBlock(list<Block>::iterator it, size_t size) {
        if (it->size > size) {
            // Create a new free block with the remaining space
            Block new_block = {0, it->size - size, true};
            memory.insert(next(it), new_block);
        }
        // Update current block
        it->size = size;
        it->is_free = false;
        it->id = next_id++;
        cout << "Allocated at ID " << it->id << endl;
    }

    // Simple visualizer
    void printMemory() {
        cout << "| ";
        for (const auto& block : memory) {
            if (block.is_free) cout << "Free (" << block.size << ") | ";
            else cout << "Alloc (" << block.size << ") | ";
        }
        cout << endl << "-----------------------------------" << endl;
    }
};

int main() {
    cout << "=== Demonstrating Standard Allocation Strategies ===" << endl;
    
    cout << "\n--- Scenario 1: First Fit ---" << endl;
    StandardAllocator ff(100);
    ff.allocateFirstFit(30);
    ff.allocateFirstFit(40);
    ff.printMemory();

    cout << "\n--- Scenario 2: Best Fit ---" << endl;
    StandardAllocator bf(100);
    bf.allocateBestFit(30);
    bf.allocateBestFit(40);
    bf.printMemory();

    return 0;
}