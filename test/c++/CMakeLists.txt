# test/c++/CMakeLists.txt

cmake_minimum_required(VERSION 3.10)
project(ATROP_CppTests LANGUAGES CXX)

# ──────────────────────────────────────────────────────────────────────────────
# 1) Enforce C++17 everywhere (so std::variant<T> and std::get<T> work).
# ──────────────────────────────────────────────────────────────────────────────
set(CMAKE_CXX_STANDARD        17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS      OFF)

include(CTest)
enable_testing()

# ──────────────────────────────────────────────────────────────────────────────
# 2) Pull in all the packages our tests need
# ──────────────────────────────────────────────────────────────────────────────
find_package(GTest       REQUIRED CONFIG)
find_package(yaml-cpp    REQUIRED CONFIG)
find_package(spdlog      REQUIRED CONFIG)
find_package(fmt         REQUIRED CONFIG)
find_package(Threads     REQUIRED)

# ──────────────────────────────────────────────────────────────────────────────
# 3) Sample Test (no extra includes needed)
# ──────────────────────────────────────────────────────────────────────────────
add_executable(test_sample
  test_sample.cpp
)
target_link_libraries(test_sample
  PRIVATE
    GTest::gtest_main
    Threads::Threads
)
add_test(NAME test_sample COMMAND test_sample)

# 
# 4) Config Loader Tests
#
#    - We must include the SDK headers so that <config_loader.hpp> is found.
#    - We link the `sdk_config_loader` library (correct library name).
# 
add_executable(test_config_loader
  test_config_loader.cpp
)
target_include_directories(test_config_loader
  PRIVATE
    ${CMAKE_SOURCE_DIR}/sdk/c++/include
    ${CMAKE_SOURCE_DIR}/sdk/c++  # Also include the legacy header location
)
target_link_libraries(test_config_loader
  PRIVATE
    sdk_config_loader      # Correct library name from sdk/c++/CMakeLists.txt
    GTest::gtest_main
    Threads::Threads
)
add_test(NAME test_config_loader COMMAND test_config_loader)


# ──────────────────────────────────────────────────────────────────────────────
# 5) Handler-stubs Test
#
#    - Include all the daemon/control_plane handler sources and the common logger.
#    - Point at your SDK headers (in case those handlers pull in config types, etc).
# ──────────────────────────────────────────────────────────────────────────────
add_executable(test_handlers
  ${CMAKE_SOURCE_DIR}/test/unit/protocol/test_handlers.cpp
  ${CMAKE_SOURCE_DIR}/daemon/control_plane/handlers/discovery_handler.cpp
  ${CMAKE_SOURCE_DIR}/daemon/control_plane/handlers/decision_handler.cpp
  ${CMAKE_SOURCE_DIR}/daemon/control_plane/handlers/observation_handler.cpp
  ${CMAKE_SOURCE_DIR}/daemon/common/logger.cpp
)
target_include_directories(test_handlers
  PRIVATE
    ${CMAKE_SOURCE_DIR}/daemon/common
    ${CMAKE_SOURCE_DIR}/daemon/control_plane
    ${CMAKE_SOURCE_DIR}/daemon/control_plane/handlers
    ${CMAKE_SOURCE_DIR}/sdk/c++/include
    ${CMAKE_SOURCE_DIR}/test/unit/protocol
)
target_link_libraries(test_handlers
  PRIVATE
    GTest::gtest_main
    yaml-cpp::yaml-cpp
    spdlog::spdlog
    fmt::fmt
    Threads::Threads
)
add_test(NAME test_handlers COMMAND test_handlers)
