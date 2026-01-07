#include <iostream>
#include <cassert>
#include "../include/buddy.h"
#include "../include/cache.h"

using namespace std;

// --- Helper Macros for Color Output ---
#define PASS "\033[32m[PASS]\033[0m"
#define FAIL "\033[31m[FAIL]\033[0m"

void test_buddy_allocator() {
    cout << "Testing Buddy Allocator..." << endl;
    
    // 1. Initialize 128KB memory
    BuddyAllocator buddy(128);
    
 
    cout << "  Requesting 16KB..." << endl;
    buddy.allocate(16); // Should split 128->64->32->16
    
    cout << "  Requesting 32KB..." << endl;
    buddy.allocate(32); // Should find 32 block
    
    // 3. Test Deallocation
    cout << "  Deallocating offset 0..." << endl;
    buddy.deallocate(0);
    
    cout << "  " << PASS << " Buddy Allocator tests finished (Visual check required for output)." << endl;
}

void test_cache_simulator() {
    cout << "\nTesting Cache Simulator..." << endl;
    
    // Setup: 4 sets, 2-way associative, 32 byte blocks
    Cache cache(4, 2, 32);
    
    // Test 1: Cold Miss
    unsigned long addr1 = 0x1000; // Tag X, Set 0
    access_cache(cache, addr1, false);
    assert(cache.misses == 1);
    cout << "  " << PASS << " Cold Miss Verified";

    // Test 2: Hit
    access_cache(cache, addr1, false);
    assert(cache.hits == 1);
    cout << " " << PASS << " Hit Verified";

    // Test 3: Eviction (Fill the set)
    // We have 2 ways. Addr1 is already there. Add 2 more addresses mapping to the same set.
    // With 32B blocks, addresses 0x2000, 0x3000 likely map to the same set index 0 if simple masking.
    unsigned long addr2 = 0x1000 + (32 * 4); // Maps to same set
    unsigned long addr3 = 0x1000 + (32 * 4 * 2); // Maps to same set
    
    access_cache(cache, addr2, false); // Miss, fills 2nd slot
    access_cache(cache, addr3, false); // Miss, should evict addr1 (LRU)
    
    assert(cache.evictions == 1);
    cout << " " << PASS << " Eviction Verified" << endl;
}

int main() {
    cout << "======================================" << endl;
    cout << "    RUNNING AUTOMATED TEST SUITE      " << endl;
    cout << "======================================" << endl;

    test_buddy_allocator();
    test_cache_simulator();

    cout << "======================================" << endl;
    cout << "       ALL TESTS COMPLETED            " << endl;
    cout << "======================================" << endl;
    return 0;
}