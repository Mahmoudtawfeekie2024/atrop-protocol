# sdk/c++/CMakeLists.txt

cmake_minimum_required(VERSION 3.14)
project(atrop_sdk_config_loader LANGUAGES CXX)

# 1) Find our dependencies
find_package(nlohmann_json CONFIG REQUIRED)
find_package(yaml-cpp       CONFIG REQUIRED)

# 2) Build the library from our two source files
add_library(sdk_config_loader
    config_loader.cpp
    config_loader.hpp
)

# 3) Create an alias so downstream users can do `sdk::config_loader`
add_library(sdk::config_loader ALIAS sdk_config_loader)

# 4) Make sure consumers can `#include "config_loader.hpp"`
target_include_directories(sdk_config_loader
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>   # when building in-tree
    $<INSTALL_INTERFACE:include/sdk>                  # after `make install`
)

# 5) Link in JSON & YAML parsers
target_link_libraries(sdk_config_loader
  PUBLIC
    nlohmann_json::nlohmann_json
    yaml-cpp::yaml-cpp
)

# ------------------------------------------------------------------------------
# Optional: install rules, so `find_package(atrop-sdk)` will work in installs
# ------------------------------------------------------------------------------

# Install the library and export its target
install(TARGETS sdk_config_loader
        EXPORT AtropSdkTargets
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin
)

# Install the public headers
install(FILES config_loader.hpp
        DESTINATION include/sdk
)

# Export the SDK targets into a <prefix>/lib/cmake/atrop-sdk folder
install(EXPORT AtropSdkTargets
        NAMESPACE sdk::
        DESTINATION lib/cmake/atrop-sdk
)
