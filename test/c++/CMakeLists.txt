cmake_minimum_required(VERSION 3.10)
project(ATROP_CppTests)

enable_testing()

# Find and configure GoogleTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Include the GoogleTest CMake module
include(GoogleTest)  # << ✅ This must be above gtest_discover_tests()

# Add test executable
add_executable(test_sample test_sample.cpp)

# Link against gtest_main and pthread
target_link_libraries(test_sample
  ${GTEST_LIBRARIES}
  GTest::gtest_main
  pthread
)

# Register tests with CTest
gtest_discover_tests(test_sample)
