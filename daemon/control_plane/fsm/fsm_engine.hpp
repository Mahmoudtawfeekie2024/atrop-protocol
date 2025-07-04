#pragma once

#include <map>
#include <memory>
#include <string>
#include <spdlog/logger.h>
#include "base_state.hpp"

// Event type for FSM transitions
enum class FSMEvent {
    RegistrationComplete,
    NeighborsMapped,
    TopologyStable,
    PolicyApproved,
    ForwardingActive,
    TelemetryThreshold,
    ModelUpdated,
    AnomalyViolation,
    FallbackRecovery,
    CorrectionApplied,
    TrustRevoked,
    NodeShutdown,
    ManualOverride,
    ManualReset,
    Unknown
};

class FSMEngine {
public:
    explicit FSMEngine(std::shared_ptr<spdlog::logger> logger);

    // Register a state with the engine
    void register_state(const std::string& state_name, std::shared_ptr<BaseState> state);

    // Transition to a new state by name (direct, for legacy/test)
    bool transition_to(const std::string& state_name);

    // Trigger a transition by event (preferred)
    bool handle_event(FSMEvent event);

    // Get the current state name
    std::string current_state_name() const;

    // Start the FSM at a given state
    void start(const std::string& initial_state);

    // Add a valid transition (from_state, event) -> to_state
    void add_transition(const std::string& from_state, FSMEvent event, const std::string& to_state);

private:
    std::map<std::string, std::shared_ptr<BaseState>> states_;
    std::shared_ptr<BaseState> current_state_;
    std::shared_ptr<spdlog::logger> logger_;

    // Transition table: (from_state, event) -> to_state
    std::map<std::pair<std::string, FSMEvent>, std::string> transition_table_;

    // Helper to stringify FSMEvent
    std::string event_to_string(FSMEvent event) const;
};
