#include <iostream>
#include <vector>
#include "../include/buddy.h"
#include "../include/cache.h"

using namespace std;

void run_buddy_demo() {
    cout << "\n--- Running Buddy Allocator Demo ---\n";
    BuddyAllocator allocator(1024);
    allocator.allocate(100);
    allocator.allocate(200);
    allocator.allocate(60);
    allocator.print_memory();
    allocator.deallocate(0);
    allocator.print_memory();
    allocator.deallocate(256);
    allocator.print_memory();
}

void run_cache_demo() {
    cout << "\n--- Running Cache Simulator Demo ---\n";
    Cache L1(32, 4, 64);
    Cache L2(256, 8, 64);

    struct TraceOp { bool is_write; unsigned long addr; };
    vector<TraceOp> trace = {
        {false, 0x1000}, {false, 0x1004}, {false, 0x1000},
        {true,  0x2000}, {false, 0x2004},
        {false, 0x3000}, {false, 0x4000}, {false, 0x5000},
        {false, 0x1000}
    };

    for(const auto& op : trace) {
        int prev_misses = L1.misses;
        access_cache(L1, op.addr, op.is_write);
        if (L1.misses > prev_misses) {
            access_cache(L2, op.addr, false);
        }
    }

    cout << "L1 Cache: Hits=" << L1.hits << ", Misses=" << L1.misses << ", Evictions=" << L1.evictions << endl;
    cout << "L2 Cache: Hits=" << L2.hits << ", Misses=" << L2.misses << ", Evictions=" << L2.evictions << endl;
}

int main() {
    int choice;
    cout << "Memory Management Simulator\n";
    cout << "1. Buddy Allocator\n";
    cout << "2. Cache Simulator\n";
    cout << "Enter choice: ";
    cin >> choice;

    if (choice == 1) run_buddy_demo();
    else if (choice == 2) run_cache_demo();
    else cout << "Invalid choice.\n";

    return 0;
}