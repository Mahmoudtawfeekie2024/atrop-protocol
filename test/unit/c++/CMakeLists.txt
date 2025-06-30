cmake_minimum_required(VERSION 3.10)
project(ATROP_Cpp_Tests)

# Enable testing framework
enable_testing()

# Find GoogleTest (system-installed)
find_package(GTest REQUIRED)

# Add include directories
include_directories(${GTEST_INCLUDE_DIRS})
include_directories(${CMAKE_SOURCE_DIR}/sdk/c++)

# Define test sources
set(TEST_SOURCES
    test_main.cpp
    test_sdk.cpp
)

# Build test executable
add_executable(test_cpp ${TEST_SOURCES})

# Link with GTest and pthread
target_link_libraries(test_cpp GTest::GTest GTest::Main pthread)

# Register with CTest
add_test(NAME ATROP_Cpp_UnitTests COMMAND test_cpp)
