# sdk/c++/CMakeLists.txt

cmake_minimum_required(VERSION 3.14)
project(atrop_sdk_config_loader LANGUAGES CXX)

# 1) Locate our dependencies
find_package(nlohmann_json CONFIG REQUIRED)
find_package(yaml-cpp       CONFIG REQUIRED)
find_package(Threads         REQUIRED)

# 2) Build the static library from our source file
add_library(sdk_config_loader STATIC
  config_loader.cpp
)

# 3) Expose its public include dir so users can do #include "config_loader.hpp"
target_include_directories(sdk_config_loader
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>      # in‐tree build
    $<INSTALL_INTERFACE:include/sdk>                     # after install()
)

# 4) Create an ALIAS so downstream can write sdk::config_loader
add_library(sdk::config_loader ALIAS sdk_config_loader)

# 5) Link in the JSON/YAML/Thread libraries
target_link_libraries(sdk_config_loader
  PUBLIC
    yaml-cpp::yaml-cpp
    nlohmann_json::nlohmann_json
    Threads::Threads
)

# 6) (Optional) Installation rules, so `find_package(atrop-sdk)` works
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
