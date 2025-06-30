cmake_minimum_required(VERSION 3.10)
project(ATROP_Cpp_Tests)

enable_testing()

# Use system gtest or FetchContent if needed
find_package(GTest REQUIRED)

include_directories(${GTEST_INCLUDE_DIRS})
include_directories(${CMAKE_SOURCE_DIR}/sdk/c++)

add_executable(test_main test_main.cpp test_sdk.cpp)

target_link_libraries(test_main GTest::GTest GTest::Main pthread)

add_test(NAME CppUnitTests COMMAND test_main)
