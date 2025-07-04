add_executable(control_plane
    main.cpp
    ../common/logger.cpp
    ../handlers/discovery_handler.cpp
    ../handlers/decision_handler.cpp
    ../handlers/observation_handler.cpp
    ../handlers/correction_handler.cpp
    ../handlers/security_handler.cpp
    ../handlers/exit_handler.cpp
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
        yaml-cpp::yaml-cpp
)
