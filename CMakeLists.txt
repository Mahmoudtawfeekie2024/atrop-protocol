cmake_minimum_required(VERSION 3.10)
project(ATROP)

enable_testing()

find_package(spdlog       REQUIRED)
find_package(fmt          REQUIRED)
find_package(yaml-cpp     REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(Threads      REQUIRED)

add_subdirectory(sdk/c++)
add_subdirectory(test/c++)
add_subdirectory(test/unit/logger)
add_subdirectory(daemon)

# (No add_executable or target_link_libraries for control_plane here)
