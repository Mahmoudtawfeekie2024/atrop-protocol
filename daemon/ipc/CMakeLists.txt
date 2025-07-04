add_executable(ipc
    main.cpp
    ../common/logger.cpp
)

target_include_directories(ipc
    PRIVATE
        ${CMAKE_SOURCE_DIR}/daemon/handlers
        ${CMAKE_SOURCE_DIR}/sdk/c++
        ${CMAKE_SOURCE_DIR}/daemon/common
)

target_link_libraries(ipc
    PRIVATE
        config_loader
        spdlog::spdlog
        fmt::fmt
        yaml-cpp
)
