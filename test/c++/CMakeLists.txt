# test/c++/CMakeLists.txt

cmake_minimum_required(VERSION 3.10)
project(ATROP_CppTests)

include(CTest)
enable_testing()

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Test 1: test_sample
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
  config_loader                   # ✅ Link the library defined in sdk/c++
  ${GTEST_LIBRARIES}
  GTest::gtest_main
  pthread
)

add_test(NAME test_config_loader COMMAND test_config_loader)

# --------------------------------------------------------
# ATROP Handler Stubs Test
# --------------------------------------------------------

add_executable(test_handlers
    ../unit/protocol/test_handlers.cpp
)

target_include_directories(test_handlers PRIVATE
    ${CMAKE_SOURCE_DIR}/daemon
    ${CMAKE_SOURCE_DIR}/daemon/common
    ${CMAKE_SOURCE_DIR}/daemon/control_plane
    ${CMAKE_SOURCE_DIR}/daemon/control_plane/handlers
    ${CMAKE_SOURCE_DIR}/sdk/c++
)

target_link_libraries(test_handlers
    gtest
    gtest_main
    pthread
    yaml-cpp::yaml-cpp
)
