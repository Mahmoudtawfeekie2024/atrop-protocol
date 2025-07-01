# test/unit/cpp/CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(ATROP_CppTests)

enable_testing()

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_test(NAME test_sample COMMAND test_sample)
add_executable(test_sample test_sample.cpp)

target_link_libraries(test_sample ${GTEST_LIBRARIES} GTest::gtest_main pthread)

add_test(NAME test_sample COMMAND test_sample)
