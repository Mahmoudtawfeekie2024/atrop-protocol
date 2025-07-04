#pragma once

#include "base_state.hpp"
#include <memory>
#include <map>
#include <string>
#include <spdlog/spdlog.h>

// Forward declaration for state pointer type
class FSMEngine {
public:
    explicit FSMEngine(std::shared_ptr<spdlog::logger> logger);

    // Register a state with the engine
    void register_state(const std::string& state_name, std::shared_ptr<BaseState> state);

    // Transition to a new state by name
    bool transition_to(const std::string& state_name);

    // Get the current state name
    std::string current_state_name() const;

    // Start the FSM at a given state
    void start(const std::string& initial_state);

private:
    std::map<std::string, std::shared_ptr<BaseState>> states_;
    std::shared_ptr<BaseState> current_state_;
    std::shared_ptr<spdlog::logger> logger_;
};
