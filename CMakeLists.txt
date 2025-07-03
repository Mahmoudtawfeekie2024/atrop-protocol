cmake_minimum_required(VERSION 3.10)
project(ATROP)

# enable CTest for add_test() and enable_testing()
enable_testing()

# find our third-party dependencies (via vcpkg or system)
find_package(spdlog       REQUIRED)
find_package(fmt          REQUIRED)
find_package(yaml-cpp     REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(Threads      REQUIRED)

# ---- SDK ----
# this brings in `sdk_config_loader` + the alias `sdk::config_loader`
add_subdirectory(sdk/c++)

# ---- Tests ----
add_subdirectory(test/c++)
add_subdirectory(test/unit/logger)

# ---- Control plane executable ----
add_executable(control_plane
    daemon/control_plane/main.cpp
    daemon/common/logger.cpp
)

target_include_directories(control_plane
    PRIVATE
        ${CMAKE_SOURCE_DIR}/sdk/c++/include    # for config_loader.hpp
        ${CMAKE_SOURCE_DIR}/daemon/common      # for logger.hpp
)

target_link_libraries(control_plane
    PRIVATE
        sdk::config_loader
        spdlog::spdlog
        fmt::fmt
        yaml-cpp::yaml-cpp
        nlohmann_json::nlohmann_json
        Threads::Threads
)

# (You can add more executables/libraries here as you expand the project)
