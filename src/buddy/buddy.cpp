#include "../../include/buddy.h"
#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

BuddyAllocator::BuddyAllocator(int size) {
    total_memory_size = size;
    memory_map.push_back({size, true, 0});
}

void BuddyAllocator::allocate(int request_size) {
    int n = ceil(log2(request_size));
    int block_size = pow(2, n);

    auto it = memory_map.begin();
    bool found = false;

    for (; it != memory_map.end(); ++it) {
        if (it->is_free && it->size >= block_size) {
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Allocation failed for size " << request_size << endl;
        return;
    }

    while (it->size > block_size) {
        int new_size = it->size / 2;
        it->size = new_size;
        it = memory_map.insert(it + 1, {new_size, true, it->offset + new_size}) - 1;
    }

    it->is_free = false;
    cout << "Allocated " << request_size << " in block size " << it->size << " at offset " << it->offset << endl;
}

void BuddyAllocator::deallocate(int offset) {
    auto it = memory_map.begin();
    bool found = false;

    for (; it != memory_map.end(); ++it) {
        if (it->offset == offset) {
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Invalid offset: " << offset << endl;
        return;
    }

    it->is_free = true;
    cout << "Freed block at offset " << offset << endl;

    while (true) {
        int current_size = it->size;
        int buddy_number = it->offset / current_size;
        int buddy_address = (buddy_number % 2 == 0) ? (it->offset + current_size) : (it->offset - current_size);

        auto buddy = memory_map.begin();
        bool buddy_found = false;
        for (; buddy != memory_map.end(); ++buddy) {
            if (buddy->offset == buddy_address && buddy->size == current_size && buddy->is_free) {
                buddy_found = true;
                break;
            }
        }

        if (buddy_found) {
            if (buddy->offset < it->offset) {
                buddy->size *= 2;
                memory_map.erase(it);
                it = buddy;
            } else {
                it->size *= 2;
                memory_map.erase(buddy);
            }
            cout << "Merged blocks into size " << it->size << endl;
        } else {
            break;
        }
    }
}

void BuddyAllocator::print_memory() {
    cout << "Memory State: ";
    for (const auto& block : memory_map) {
        cout << "[" << block.size << (block.is_free ? "F" : "A") << "] ";
    }
    cout << endl;
}