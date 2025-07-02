cmake_minimum_required(VERSION 3.10)
project(ATROP_CppTests)

include(CTest)
enable_testing()

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# ✅ Test 1: test_sample
add_executable(test_sample test_sample.cpp)
target_link_libraries(test_sample
  ${GTEST_LIBRARIES}
  GTest::gtest_main
  pthread
)
add_test(NAME test_sample COMMAND test_sample)

# ✅ Test 2: test_config_loader
add_executable(test_config_loader test_config_loader.cpp)
target_link_libraries(test_config_loader
  config_loader               # ✅ Link your SDK implementation
  ${GTEST_LIBRARIES}
  GTest::gtest_main
  pthread
)
add_test(NAME test_config_loader COMMAND test_config_loader)
