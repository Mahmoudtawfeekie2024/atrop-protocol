cmake_minimum_required(VERSION 3.10)
project(ATROP_CppTests)

include(CTest)
enable_testing()

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(test_sample test_sample.cpp)

target_link_libraries(test_sample
  ${GTEST_LIBRARIES}
  GTest::gtest_main
  pthread
)

include(GoogleTest)
gtest_discover_tests(test_sample
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/test/c++
  DISCOVERY_TIMEOUT 10
)
