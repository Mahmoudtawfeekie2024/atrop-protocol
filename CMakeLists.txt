cmake_minimum_required(VERSION 3.14)
project(ATROP LANGUAGES CXX)

# enable `ctest` / `make test`
enable_testing()

# 1) find dependencies (via vcpkg or system)
find_package(spdlog        REQUIRED)
find_package(fmt           REQUIRED)
find_package(yaml-cpp      REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(Threads       REQUIRED)
find_package(GTest         CONFIG REQUIRED)

# 2) build our SDK
add_subdirectory(sdk/c++)

# 3) build our control‐plane binary
add_executable(control_plane
  daemon/control_plane/main.cpp
  daemon/common/logger.cpp
)
target_link_libraries(control_plane
  PRIVATE
    sdk::config_loader      # ← our SDK alias
    spdlog::spdlog
    fmt::fmt
    yaml-cpp::yaml-cpp
    Threads::Threads
)
# the SDK EXPORT already makes its include dir visible,
# so we only need to expose our own headers here:
target_include_directories(control_plane
  PRIVATE
    ${CMAKE_SOURCE_DIR}/daemon/common
)

# 4) build all tests
add_subdirectory(test/c++)
add_subdirectory(test/unit/logger)
