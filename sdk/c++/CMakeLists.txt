cmake_minimum_required(VERSION 3.14)
project(atrop_sdk_config_loader LANGUAGES CXX)

# 1) Find only what we need
find_package(nlohmann_json CONFIG REQUIRED)
find_package(yaml-cpp       CONFIG REQUIRED)
find_package(Threads        REQUIRED)

# 2) Build the static library from our implementation
add_library(sdk_config_loader STATIC
  config_loader.cpp
)
add_library(sdk::config_loader ALIAS sdk_config_loader)

# 3) Public headers live in `include/`
target_include_directories(sdk_config_loader
  PUBLIC
    # for in-tree builds:
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    # for installed usage:
    $<INSTALL_INTERFACE:include/sdk>
)

# 4) Link in JSON/YAML/threading deps
target_link_libraries(sdk_config_loader
  PUBLIC
    nlohmann_json::nlohmann_json
    yaml-cpp::yaml-cpp
    Threads::Threads
)

# 5) Installation rules so downstream `find_package(atrop-sdk)` works
install(TARGETS sdk_config_loader
        EXPORT AtropSdkTargets
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin
)
install(FILES include/config_loader.hpp
        DESTINATION include/sdk
)
install(EXPORT AtropSdkTargets
        NAMESPACE sdk::
        DESTINATION lib/cmake/atrop-sdk
)
