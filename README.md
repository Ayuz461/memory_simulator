# Memory Management Simulator

## Project Overview
This project is a comprehensive **C++ simulation of an Operating System's Memory Management Unit (MMU)**. It implements critical hardware and kernel-level components to demonstrate how computers manage physical memory and high-speed caching.

The simulator covers three distinct phases of memory management:
1.  **Physical Memory Allocation:** Implemented using the **Buddy System** algorithm to minimize external fragmentation.
2.  **Cache Hierarchy Simulation:** A configurable **L1/L2 Cache** controller with LRU (Least Recently Used) eviction policies.
3.  **Simple Allocation:** A baseline allocator for comparison (Phase 1).

---

## Features

### 1. Buddy System Allocator (Physical Memory)
* **Algorithm:** Manages memory blocks using power-of-two subdivision.
* **Splitting:** Recursively splits larger blocks to find the "best fit" for a request.
* **Coalescing:** Automatically merges adjacent free "buddies" upon deallocation to defragment memory.
* **Efficiency:** Uses strict bitwise logic for high-speed block address calculations.

### 2. Multi-Level Cache Simulator
* **Hierarchy:** Simulates a split L1 (Level 1) and L2 (Level 2) cache architecture.
* **Configurable Parameters:** Supports custom Set counts, Associativity (N-way), and Block sizes.
* **Logic:**
    * **Bitwise Addressing:** Extracts *Tag*, *Index*, and *Offset* bits from raw memory addresses.
    * **LRU Eviction:** Tracks usage history to evict the least recently used lines when sets are full.
    * **Hit/Miss/Eviction Tracking:** Detailed statistics on simulation performance.

---

## 📂 Project Structure

```text
memory-simulator/
├── Makefile                   # Automated build script
├── README.md                  # Project documentation
├── include/                   # Header files (.h)
│   ├── buddy.h
│   └── cache.h
├── src/                       # Source code (.cpp)
│   ├── main.cpp               # Interactive menu and entry point
│   ├── allocator/             # Phase 1: Simple Allocator
│   │   └── simple_allocator.cpp
│   ├── buddy/                 # Phase 2: Buddy System Logic
│   │   └── buddy.cpp
│   └── cache/                 # Phase 3: L1/L2 Cache Logic
│       └── cache.cpp
└── tests/                     # Automated Test Suites
    └── test_suite.cpp


->Build & Installation
Prerequisites
C++ Compiler: GCC (g++) or Clang supporting C++11 or higher.

Make: GNU Make utility.

Compilation
To compile the main simulator:

Bash

make
This generates the executable memory_sim.

To compile the test suite:

Bash

make test
This generates the executable run_tests.

-> Usage
1. Running the Simulator
Launch the interactive dashboard to see the allocators in action:

Bash

./memory_sim
Menu Options:

Option 1 (Buddy Allocator): Demonstrates allocating 100KB, splitting blocks, and merging them back upon free.

Option 2 (Cache Simulator): Runs a trace of memory accesses (Reads/Writes) through L1 and L2 caches and reports Hit/Miss rates.

2. Running Automated Tests
Verify the logic integrity using the test suite:

Bash

./run_tests
Expected Output:

Verifies correct splitting of 128KB blocks down to 16KB.

Verifies "Cold Misses" and "Hits" in the Cache.

Verifies LRU Eviction behaves correctly when a cache set is full.

-> Technical Details
The Buddy Math
For a block of size 2^k at address A, the address of its buddy is calculated using XOR: Buddy(A) = A XOR 2^k This allows the allocator to find neighbors instantly without searching the entire list.

Cache Addressing
A 32-bit address is split dynamically based on cache configuration:

Tag Bits: Identity of the memory block.

Set Index Bits: Log2(NumSets).

Offset Bits: Log2(BlockSize).

-->>Author
Name: Ayush Patil(22323010)

Department: Mathematics and Computing 4y, IIT Roorkee

