add_executable(control_plane
    main.cpp
    ../common/logger.cpp
)

target_include_directories(control_plane
    PRIVATE
        ${CMAKE_SOURCE_DIR}/daemon/handlers
        ${CMAKE_SOURCE_DIR}/sdk/c++
        ${CMAKE_SOURCE_DIR}/daemon/common
)

target_link_libraries(control_plane
    PRIVATE
        config_loader
        spdlog::spdlog
        fmt::fmt
        yaml-cpp
)
