cmake_minimum_required(VERSION 3.10)
project(ATROP_CppTests)

include(CTest)
enable_testing()

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# ===== Existing test_sample =====
add_executable(test_sample test_sample.cpp)

target_link_libraries(test_sample
  ${GTEST_LIBRARIES}
  GTest::gtest_main
  pthread
)

add_test(NAME test_sample COMMAND test_sample)

# ===== New: test_config_loader =====
add_executable(test_config_loader test_config_loader.cpp)

target_include_directories(test_config_loader PRIVATE ../../sdk/c++)
target_link_libraries(test_config_loader
  ${GTEST_LIBRARIES}
  GTest::gtest_main
  pthread
)

add_test(NAME test_config_loader COMMAND test_config_loader)
