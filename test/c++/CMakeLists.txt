# test/c++/CMakeLists.txt

cmake_minimum_required(VERSION 3.10)
project(ATROP_CppTests LANGUAGES CXX)

# ─── Require C++17 for std::variant, std::get<T>, etc.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(CTest)
enable_testing()

# ─── Find all our test‐time dependencies
find_package(GTest       REQUIRED CONFIG)
find_package(yaml-cpp    REQUIRED CONFIG)
find_package(spdlog      REQUIRED CONFIG)
find_package(fmt         REQUIRED CONFIG)
find_package(Threads     REQUIRED)

# ─── Sample Test
add_executable(test_sample
  test_sample.cpp
)
target_link_libraries(test_sample
  PRIVATE
    GTest::gtest_main
    Threads::Threads
)
add_test(NAME test_sample COMMAND test_sample)

# ─── Config Loader Test
add_executable(test_config_loader
  test_config_loader.cpp
)
# so that #include <config_loader.hpp> works
target_include_directories(test_config_loader PRIVATE
  ${CMAKE_SOURCE_DIR}/sdk/c++/include
)
target_link_libraries(test_config_loader
  PRIVATE
    sdk::config_loader    # pulls in json/yaml/thread deps transitively
    GTest::gtest_main
    Threads::Threads
)
add_test(NAME test_config_loader COMMAND test_config_loader)

# ─── Handler‐Stubs Test
add_executable(test_handlers
  ${CMAKE_SOURCE_DIR}/test/unit/protocol/test_handlers.cpp
  ${CMAKE_SOURCE_DIR}/daemon/control_plane/handlers/discovery_handler.cpp
  ${CMAKE_SOURCE_DIR}/daemon/control_plane/handlers/decision_handler.cpp
  ${CMAKE_SOURCE_DIR}/daemon/control_plane/handlers/observation_handler.cpp
  ${CMAKE_SOURCE_DIR}/daemon/common/logger.cpp
)
target_include_directories(test_handlers PRIVATE
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
