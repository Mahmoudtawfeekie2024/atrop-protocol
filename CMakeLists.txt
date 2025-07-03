cmake_minimum_required(VERSION 3.14)
project(ATROP LANGUAGES CXX)

# enable ctest() / make test
enable_testing()

# ------------------------------------------------------------------------------
# 1) Pull in global deps (via vcpkg or system)
# ------------------------------------------------------------------------------

find_package(spdlog        REQUIRED)
find_package(fmt           REQUIRED)
find_package(yaml-cpp      REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(Threads       REQUIRED)
find_package(GTest         CONFIG REQUIRED)

# ------------------------------------------------------------------------------
# 2) Build our SDK (config_loader) from sdk/c++
# ------------------------------------------------------------------------------
add_subdirectory(sdk/c++)

# ------------------------------------------------------------------------------
# 3) Build unit/integration tests
# ------------------------------------------------------------------------------
add_subdirectory(test/c++)
add_subdirectory(test/unit/logger)

# ------------------------------------------------------------------------------
# 4) Build the control_plane executable
# ------------------------------------------------------------------------------
add_executable(control_plane
  daemon/control_plane/main.cpp
  daemon/common/logger.cpp
)

# expose the SDK include path so `#include <config_loader.hpp>` works
target_include_directories(control_plane
  PRIVATE
    ${CMAKE_SOURCE_DIR}/sdk/c++
    ${CMAKE_SOURCE_DIR}/daemon/common
)

# link the SDK & other libs
target_link_libraries(control_plane
  PRIVATE
    sdk::config_loader
    spdlog::spdlog
    fmt::fmt
    yaml-cpp::yaml-cpp
    Threads::Threads
)
