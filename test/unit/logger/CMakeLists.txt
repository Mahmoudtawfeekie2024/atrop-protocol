cmake_minimum_required(VERSION 3.14)

project(logger_test)

# Find required packages
find_package(GTest REQUIRED CONFIG)
# Use CONFIG mode and tell it to look in VCPKG paths
find_package(spdlog CONFIG REQUIRED)
find_package(fmt REQUIRED)

add_executable(logger_test
  ${CMAKE_SOURCE_DIR}/test/unit/logger/test_logger.cpp
  ${CMAKE_SOURCE_DIR}/daemon/common/logger.cpp
)

target_include_directories(logger_test PRIVATE
  ${CMAKE_SOURCE_DIR}/daemon/common
)

target_link_libraries(logger_test
  PRIVATE GTest::gtest GTest::gtest_main spdlog::spdlog fmt::fmt
)
