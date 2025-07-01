cmake_minimum_required(VERSION 3.10)
project(ATROP_CppTests)

# 👇👇👇 THIS is what activates test registration via gtest_discover_tests()
include(CTest)
enable_testing()

# ✅ Find GoogleTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# ✅ Define the test executable
add_executable(test_sample test_sample.cpp)

# ✅ Link everything
target_link_libraries(test_sample
  ${GTEST_LIBRARIES}
  GTest::gtest_main
  pthread
)

# ✅ Discover the tests
include(GoogleTest)
gtest_discover_tests(test_sample)
