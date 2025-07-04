cmake_minimum_required(VERSION 3.10)
project(ATROP)

enable_testing()

# Find required packages (installed via vcpkg)
find_package(spdlog REQUIRED)
find_package(fmt REQUIRED)
find_package(yaml-cpp REQUIRED)

# Add SDK and Test modules
add_subdirectory(sdk/c++)
add_subdirectory(test/c++)
add_subdirectory(test/unit/logger)

# Add control plane executable with sources
add_executable(daemon/control_plane
    daemon/control_plane/main.cpp
    daemon/common/logger.cpp
    daemon/handlers/discovery_handler.cpp
    daemon/handlers/decision_handler.cpp
    daemon/handlers/observation_handler.cpp
    daemon/handlers/correction_handler.cpp
    daemon/handlers/security_handler.cpp
    daemon/handlers/exit_handler.cpp
)

target_include_directories(control_plane
    PRIVATE
        ${CMAKE_SOURCE_DIR}/sdk/c++        # for config_loader.hpp
        ${CMAKE_SOURCE_DIR}/daemon/common  # for logger.hpp
        ${CMAKE_SOURCE_DIR}/daemon/handlers
)

target_link_libraries(control_plane
    PRIVATE
        config_loader
        spdlog::spdlog
        fmt::fmt
        yaml-cpp::yaml-cpp
)
