CXX = g++
CXXFLAGS = -Iinclude -Wall -std=c++11

# Source files for the MAIN application
SRCS_MAIN = src/main.cpp src/buddy/buddy.cpp src/cache/cache.cpp
TARGET_MAIN = memory_sim

# Source files for the TEST suite
# We link the test file with the buddy/cache logic, but NOT src/main.cpp
SRCS_TEST = tests/test_suite.cpp src/buddy/buddy.cpp src/cache/cache.cpp
TARGET_TEST = run_tests

# Rule to build the main simulator
all:
	$(CXX) $(CXXFLAGS) $(SRCS_MAIN) -o $(TARGET_MAIN)

# Rule to build the test suite
test:
	$(CXX) $(CXXFLAGS) $(SRCS_TEST) -o $(TARGET_TEST)

# Clean both
clean:
	rm -f $(TARGET_MAIN) $(TARGET_TEST)