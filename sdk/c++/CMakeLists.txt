cmake_minimum_required(VERSION 3.14)
project(atrop_sdk_config_loader LANGUAGES CXX)

#— find our dependencies (via vcpkg or system)
find_package(nlohmann_json  CONFIG REQUIRED)
find_package(yaml-cpp        CONFIG REQUIRED)
find_package(Threads         REQUIRED)

#— build the static SDK library
add_library(sdk_config_loader STATIC
  config_loader.cpp
)

#— expose a clean alias for downstream
add_library(sdk::config_loader ALIAS sdk_config_loader)

#— make sure consumers can #include "config_loader.hpp"
#   (we assume config_loader.hpp lives alongside config_loader.cpp in this folder)
target_include_directories(sdk_config_loader
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>    # in-tree builds
    $<INSTALL_INTERFACE:include/sdk>                   # after `make install`
)

#— link in JSON, YAML and pthread
target_link_libraries(sdk_config_loader
  PUBLIC
    nlohmann_json::nlohmann_json
    yaml-cpp::yaml-cpp
    Threads::Threads
)

#— optional install rules so you can `find_package(atrop-sdk)` after install()
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
