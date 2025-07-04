cmake_minimum_required(VERSION 3.10)
project(ATROP)

enable_testing()

# Find required packages (installed via vcpkg)
find_package(spdlog REQUIRED)
find_package(fmt REQUIRED)
find_package(yaml-cpp REQUIRED)

# Add SDK and Test modules
add_subdirectory(sdk/c++)
add_subdirectory(daemon/control_plane)
add_subdirectory(test/c++)
add_subdirectory(test/unit/logger)
