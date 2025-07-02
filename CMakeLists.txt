cmake_minimum_required(VERSION 3.10)
project(ATROP)

add_subdirectory(test/c++)
enable_testing()

add_library(config_loader config_loader.cpp)

target_include_directories(config_loader PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(config_loader PRIVATE yaml-cpp nlohmann_json::nlohmann_json)
