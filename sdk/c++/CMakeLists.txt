cmake_minimum_required(VERSION 3.14)
project(atrop_sdk_config_loader LANGUAGES CXX)

# 1) pull in json, yaml, pthread
find_package(nlohmann_json CONFIG REQUIRED)
find_package(yaml-cpp       CONFIG REQUIRED)
find_package(Threads        REQUIRED)

# 2) build the static library from config_loader.cpp
add_library(sdk_config_loader STATIC
    config_loader.cpp
)

# 3) give downstreams a nice alias
add_library(sdk::config_loader ALIAS sdk_config_loader)

# 4) expose our include dir so they can #include "config_loader.hpp"
target_include_directories(sdk_config_loader
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>    # in-tree builds
    $<INSTALL_INTERFACE:include/sdk>                   # install prefix
)

# 5) link in json, yaml, threads
target_link_libraries(sdk_config_loader
  PUBLIC
    nlohmann_json::nlohmann_json
    yaml-cpp::yaml-cpp
    Threads::Threads
)

# 6) optional install rules so `find_package(atrop-sdk)` works post-install
install(TARGETS sdk_config_loader
        EXPORT AtropSdkTargets
        ARCHIVE   DESTINATION lib
        LIBRARY   DESTINATION lib
        RUNTIME   DESTINATION bin
)
install(FILES config_loader.hpp
        DESTINATION include/sdk
)
install(EXPORT AtropSdkTargets
        NAMESPACE sdk::
        DESTINATION lib/cmake/atrop-sdk
)
