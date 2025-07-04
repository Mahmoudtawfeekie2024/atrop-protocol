cmake_minimum_required(VERSION 3.10)
project(ATROP_CppTests)

include(CTest)
enable_testing()

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
include_directories(${CMAKE_SOURCE_DIR}/sdk/c++)
include_directories(${CMAKE_SOURCE_DIR}/daemon/handlers)

# Test 1: test_sample
add_executable(test_sample test_sample.cpp)
target_link_libraries(test_sample
  ${GTEST_LIBRARIES}
  GTest::gtest_main
  pthread
)
add_test(NAME test_sample COMMAND test_sample)

# Test 2: test_config_loader
add_executable(test_config_loader test_config_loader.cpp)
target_link_libraries(test_config_loader
  config_loader                   # Link the library defined in sdk/c++
  ${GTEST_LIBRARIES}
  GTest::gtest_main
  pthread
)
add_test(NAME test_config_loader COMMAND test_config_loader)

# Test 3: handler_test
add_executable(handler_test
    test_handlers.cpp
    ${CMAKE_SOURCE_DIR}/daemon/handlers/discovery_handler.cpp
    ${CMAKE_SOURCE_DIR}/daemon/handlers/decision_handler.cpp
    ${CMAKE_SOURCE_DIR}/daemon/handlers/observation_handler.cpp
    ${CMAKE_SOURCE_DIR}/daemon/handlers/correction_handler.cpp
    ${CMAKE_SOURCE_DIR}/daemon/handlers/security_handler.cpp
    ${CMAKE_SOURCE_DIR}/daemon/handlers/exit_handler.cpp
)
target_link_libraries(handler_test
  ${GTEST_LIBRARIES}
  GTest::gtest_main
  pthread
)
add_test(NAME handler_test COMMAND handler_test)

# Test 4: test_fsm
add_executable(test_fsm test_fsm.cpp)
target_link_libraries(test_fsm
  ${GTEST_LIBRARIES}
  GTest::gtest_main
  pthread
)
add_test(NAME test_fsm COMMAND test_fsm)
