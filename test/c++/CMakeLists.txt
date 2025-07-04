cmake_minimum_required(VERSION 3.10)
project(ATROP_CppTests)

include(CTest)
enable_testing()

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
include_directories(${CMAKE_SOURCE_DIR}/sdk/c++)
include_directories(${CMAKE_SOURCE_DIR}/daemon/handlers)

# Add the project root to the include path
set(FSM_INCLUDE_DIRS
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/daemon/control_plane/fsm
    ${CMAKE_SOURCE_DIR}/daemon/control_plane/fsm/states
    ${CMAKE_SOURCE_DIR}/daemon/control_plane
)

add_executable(test_sample test_sample.cpp)
target_include_directories(test_sample PRIVATE ${FSM_INCLUDE_DIRS})
target_link_libraries(test_sample
  ${GTEST_LIBRARIES}
  GTest::gtest_main
  pthread
)
add_test(NAME test_sample COMMAND test_sample)

add_executable(test_config_loader test_config_loader.cpp)
target_include_directories(test_config_loader PRIVATE ${FSM_INCLUDE_DIRS})
target_link_libraries(test_config_loader
  config_loader
  ${GTEST_LIBRARIES}
  GTest::gtest_main
  pthread
)
add_test(NAME test_config_loader COMMAND test_config_loader)

add_executable(handler_test
    test_handlers.cpp
    ${CMAKE_SOURCE_DIR}/daemon/handlers/discovery_handler.cpp
    ${CMAKE_SOURCE_DIR}/daemon/handlers/decision_handler.cpp
    ${CMAKE_SOURCE_DIR}/daemon/handlers/observation_handler.cpp
    ${CMAKE_SOURCE_DIR}/daemon/handlers/correction_handler.cpp
    ${CMAKE_SOURCE_DIR}/daemon/handlers/security_handler.cpp
    ${CMAKE_SOURCE_DIR}/daemon/handlers/exit_handler.cpp
)
target_include_directories(handler_test PRIVATE ${FSM_INCLUDE_DIRS})
target_link_libraries(handler_test
  ${GTEST_LIBRARIES}
  GTest::gtest_main
  pthread
)
add_test(NAME handler_test COMMAND handler_test)

add_executable(test_fsm test_fsm.cpp)
target_include_directories(test_fsm PRIVATE ${FSM_INCLUDE_DIRS})
target_link_libraries(test_fsm
  ${GTEST_LIBRARIES}
  GTest::gtest_main
  pthread
)
add_test(NAME test_fsm COMMAND test_fsm)
