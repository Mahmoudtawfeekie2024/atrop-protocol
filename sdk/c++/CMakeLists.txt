cmake_minimum_required(VERSION 3.14)
project(atrop_sdk_config_loader LANGUAGES CXX)

# 1) find exactly what we need
find_package(nlohmann_json CONFIG REQUIRED)
find_package(yaml-cpp       CONFIG REQUIRED)
find_package(Threads        REQUIRED)

# 2) build the static library
add_library(sdk_config_loader STATIC
  config_loader.cpp
)

# 3) create a proper alias for downstream linkers
add_library(sdk::config_loader ALIAS sdk_config_loader)

# 4) make sure both in‐tree builds and installed usage work
target_include_directories(sdk_config_loader
  PUBLIC
    # when building in-tree:
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    # when installed via `make install`:
    $<INSTALL_INTERFACE:include/sdk>
)

# 5) link our JSON/YAML/thread deps
target_link_libraries(sdk_config_loader
  PUBLIC
    nlohmann_json::nlohmann_json
    yaml-cpp::yaml-cpp
    Threads::Threads
)

# 6) install rules so `find_package(atrop-sdk)` works post-install
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
