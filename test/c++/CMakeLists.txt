# test/c++/CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(ATROP_CppTests)

enable_testing()

# Find GoogleTest and include its headers
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Define the test binary
add_executable(test_sample test_sample.cpp)

# Link against GTest and pthread (required by GTest)
target_link_libraries(test_sample
  ${GTEST_LIBRARIES}
  GTest::gtest_main
  pthread
)

# Register the test with CTest
add_test(NAME test_sample COMMAND test_sample)
