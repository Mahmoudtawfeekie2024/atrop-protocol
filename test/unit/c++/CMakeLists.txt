cmake_minimum_required(VERSION 3.10)
project(ATROP_Cpp_Tests)

# Enable testing framework
enable_testing()

# Find GoogleTest (system-installed or via vcpkg)
find_package(GTest REQUIRED)

# Add include directories
include_directories(${GTEST_INCLUDE_DIRS})
include_directories(${CMAKE_SOURCE_DIR}/sdk/c++)
include_directories(${CMAKE_SOURCE_DIR}/daemon/common)
include_directories(${CMAKE_SOURCE_DIR}/daemon/control_plane/handlers)

# --------------------------
# Build test_cpp (original tests)
# --------------------------

set(TEST_SOURCES
    test_main.cpp
    test_sdk.cpp
)

add_executable(test_cpp ${TEST_SOURCES})

target_link_libraries(test_cpp
    GTest::GTest
    GTest::Main
    pthread
)

add_test(NAME ATROP_Cpp_UnitTests COMMAND test_cpp)

# --------------------------
# Build test_handlers
# --------------------------

add_executable(test_handlers
    ../unit/protocol/test_handlers.cpp
)

target_link_libraries(test_handlers
    GTest::GTest
    GTest::Main
    pthread
)

add_test(NAME HandlerStubTests COMMAND test_handlers)
