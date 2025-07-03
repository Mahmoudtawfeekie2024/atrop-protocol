# CMakeLists.txt (top‐level)

cmake_minimum_required(VERSION 3.10)
project(ATROP LANGUAGES CXX)

enable_testing()

# 1) Third-party libraries (installed via vcpkg, apt, etc.)
find_package(spdlog       REQUIRED)
find_package(fmt          REQUIRED)
find_package(yaml-cpp     REQUIRED)
find_package(Threads      REQUIRED)

# 2) Pull in our SDK
add_subdirectory(sdk/c++)

# 3) Any test subdirs
add_subdirectory(test/c++)
add_subdirectory(test/unit/logger)

# 4) Build the control_plane binary
add_executable(control_plane
    daemon/control_plane/main.cpp
    daemon/common/logger.cpp
)

# 5) It only needs to know about its own headers plus our common logger
target_include_directories(control_plane
  PRIVATE
    ${CMAKE_SOURCE_DIR}/daemon/common
)

# 6) Link against our alias plus the rest of the libs
target_link_libraries(control_plane
  PRIVATE
    sdk::config_loader      # <-- pulls in config_loader.hpp and its deps
    spdlog::spdlog
    fmt::fmt
    yaml-cpp::yaml-cpp
    Threads::Threads
)
