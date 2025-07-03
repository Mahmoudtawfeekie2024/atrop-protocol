cmake_minimum_required(VERSION 3.14)
project(ATROP LANGUAGES CXX)

# for vcpkg users this is passed in via -DCMAKE_TOOLCHAIN_FILE, etc.
enable_testing()

# common dependencies (all provided by vcpkg or system)
find_package(spdlog        REQUIRED)
find_package(fmt           REQUIRED)
find_package(yaml-cpp      REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(Threads       REQUIRED)
find_package(GTest         CONFIG REQUIRED)

# 1) build our SDK (config_loader) library
add_subdirectory(sdk/c++)

# 2) build any tests you have
add_subdirectory(test/c++)
add_subdirectory(test/unit/logger)

# 3) build our control_plane binary
add_executable(control_plane
    daemon/control_plane/main.cpp
    daemon/common/logger.cpp
)

# 4) link it against the SDK + other deps
target_link_libraries(control_plane
  PRIVATE
    sdk::config_loader    # <- brings in config_loader.hpp + json+yaml+threads
    spdlog::spdlog
    fmt::fmt
    yaml-cpp::yaml-cpp
    Threads::Threads
)
