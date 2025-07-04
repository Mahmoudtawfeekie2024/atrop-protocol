add_executable(control_plane
    main.cpp
    ../common/logger.cpp
    ../handlers/discovery_handler.cpp
    ../handlers/decision_handler.cpp
    ../handlers/observation_handler.cpp
    ../handlers/correction_handler.cpp
    ../handlers/security_handler.cpp
    ../handlers/exit_handler.cpp

    # FSM engine and base
    fsm/base_state.cpp
    fsm/fsm_engine.cpp

    # FSM states
    fsm/states/init_state.cpp
    fsm/states/discovery_state.cpp
    fsm/states/learn_state.cpp
    fsm/states/decide_state.cpp
    fsm/states/enforce_state.cpp
    fsm/states/observe_state.cpp
    fsm/states/feedback_state.cpp
    fsm/states/correct_state.cpp
    fsm/states/exit_state.cpp
)

target_include_directories(control_plane
    PRIVATE
        ${CMAKE_SOURCE_DIR}/daemon/handlers
        ${CMAKE_SOURCE_DIR}/sdk/c++
        ${CMAKE_SOURCE_DIR}/daemon/common
        ${CMAKE_SOURCE_DIR}/daemon/control_plane/fsm
        ${CMAKE_SOURCE_DIR}/daemon/control_plane/fsm/states
)

target_link_libraries(control_plane
    PRIVATE
        config_loader
        spdlog::spdlog
        fmt::fmt
        yaml-cpp::yaml-cpp
)
