# sdk/c++/CMakeLists.txt
cmake_minimum_required(VERSION 3.14)
project(atrop_sdk_config_loader LANGUAGES CXX)

# 1) Find dependencies
find_package(nlohmann_json CONFIG REQUIRED)
find_package(yaml-cpp       CONFIG REQUIRED)

# 2) Build only the sdk_config_loader library
add_library(sdk_config_loader STATIC
  config_loader.cpp
)

# 3) Expose includes so users can do #include "config_loader.hpp"
target_include_directories(sdk_config_loader
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>  # in-tree builds
    $<INSTALL_INTERFACE:include/sdk>                 # after install()
)

# 4) Give it a nice alias
add_library(sdk::config_loader ALIAS sdk_config_loader)

# 5) Link in JSON/YAML parsers
target_link_libraries(sdk_config_loader
  PUBLIC
    nlohmann_json::nlohmann_json
    yaml-cpp::yaml-cpp
)

# 6) (Optional) install rules so downstream projects can find_package(atrop-sdk)
install(TARGETS sdk_config_loader
        EXPORT AtropSdkTargets
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin
)

install(FILES config_loader.hpp
        DESTINATION include/sdk
)

install(EXPORT AtropSdkTargets
        NAMESPACE sdk::
        DESTINATION lib/cmake/atrop-sdk
)
