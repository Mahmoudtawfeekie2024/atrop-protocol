add_library(control_plane_fsm
    fsm/fsm_main.cpp
    fsm/state_exit.cpp
    fsm/state_decide.cpp
    fsm/state_feedback.cpp
    fsm/state_discovery.cpp
    fsm/state_learn.cpp
    fsm/state_enforce.cpp
    fsm/state_observe.cpp
    fsm/state_correct.cpp
    fsm/fsm_engine.cpp
    fsm/state_init.cpp
    handlers/observation_handler.cpp
    handlers/decision_handler.cpp
    handlers/discovery_handler.cpp
)

add_executable(control_plane main.cpp)
target_link_libraries(control_plane PRIVATE control_plane_fsm Threads::Threads spdlog::spdlog)
target_link_libraries(control_plane_fsm PRIVATE spdlog::spdlog)

target_include_directories(control_plane_fsm
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../common
        ${CMAKE_SOURCE_DIR}/sdk/c++
)

target_include_directories(control_plane
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../common
        ${CMAKE_SOURCE_DIR}/sdk/c++
)
