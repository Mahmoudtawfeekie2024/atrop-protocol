cmake_minimum_required(VERSION 3.14)
project(atrop_sdk_config_loader LANGUAGES CXX)

# ------------------------------------------------------------------------------
# 1) Find exactly what we need
# ------------------------------------------------------------------------------
find_package(nlohmann_json CONFIG REQUIRED)
find_package(yaml-cpp       CONFIG REQUIRED)
find_package(Threads        REQUIRED)

# ------------------------------------------------------------------------------
# 2) Build our static library from these two files:
#    - config_loader.hpp
#    - config_loader.cpp
# ------------------------------------------------------------------------------
add_library(sdk_config_loader STATIC
  config_loader.cpp
)

# ------------------------------------------------------------------------------
# 3) Create a namespaced alias so downstream can do `sdk::config_loader`
# ------------------------------------------------------------------------------
add_library(sdk::config_loader ALIAS sdk_config_loader)

# ------------------------------------------------------------------------------
# 4) Make sure both the implementation and users can find the headers
# ------------------------------------------------------------------------------
target_include_directories(sdk_config_loader
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}         # so config_loader.cpp can #include "config_loader.hpp"
)

# ------------------------------------------------------------------------------
# 5) Link in JSON, YAML, pthread
# ------------------------------------------------------------------------------
target_link_libraries(sdk_config_loader
  PUBLIC
    nlohmann_json::nlohmann_json
    yaml-cpp::yaml-cpp
    Threads::Threads
)

# ------------------------------------------------------------------------------
# 6) (Optional) install rules for `make install` + downstream `find_package(atrop-sdk)`
# ------------------------------------------------------------------------------
install(TARGETS sdk_config_loader
        EXPORT AtropSdkTargets
        ARCHIVE  DESTINATION lib
        LIBRARY  DESTINATION lib
        RUNTIME  DESTINATION bin
)

install(FILES config_loader.hpp
        DESTINATION include/sdk
)

install(EXPORT AtropSdkTargets
        NAMESPACE sdk::
        DESTINATION lib/cmake/atrop-sdk
)
