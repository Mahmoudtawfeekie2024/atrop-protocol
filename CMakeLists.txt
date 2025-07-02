cmake_minimum_required(VERSION 3.10)
project(ATROP)

enable_testing()

# Add SDK and Test modules
add_subdirectory(sdk/c++)
add_subdirectory(test/c++)

# Add control plane executable
add_executable(control_plane daemon/control_plane/main.cpp)

target_include_directories(control_plane
    PRIVATE
        ${CMAKE_SOURCE_DIR}/sdk/c++    # config_loader.hpp
)

target_link_libraries(control_plane
    PRIVATE
        config_loader
)
