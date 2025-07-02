cmake_minimum_required(VERSION 3.10)
project(ATROP)

enable_testing()

# Add SDK and Test modules
add_subdirectory(sdk/c++)
add_subdirectory(test/c++)
add_subdirectory(test/unit/logger)

# Add control plane executable with required sources and include paths
add_executable(control_plane
    daemon/control_plane/main.cpp
    daemon/common/logger.cpp
)

target_include_directories(control_plane
    PRIVATE
        ${CMAKE_SOURCE_DIR}/sdk/c++        # For config_loader.hpp
        ${CMAKE_SOURCE_DIR}/daemon/common  # For logger.hpp
)

target_link_libraries(control_plane
    PRIVATE
        config_loader
        spdlog::spdlog
        fmt::fmt
        yaml-cpp
)
