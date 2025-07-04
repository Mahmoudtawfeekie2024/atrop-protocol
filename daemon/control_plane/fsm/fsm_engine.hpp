#pragma once

#include <string>
#include <map>
#include <memory>
#include "base_state.hpp"
#include <spdlog/spdlog.h>

// --- FSMEvent Enum Definition ---
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
    ManualReset
};

// --- FSMEngine Class Definition ---
class FSMEngine {
public:
    explicit FSMEngine(std::shared_ptr<spdlog::logger> logger);

    void register_state(const std::string& name, std::shared_ptr<BaseState> state);
    void add_transition(const std::string& from, FSMEvent event, const std::string& to);
    void start(const std::string& initial_state);
    void handle_event(FSMEvent event);

    // Utility: Convert FSMEvent to string
    static std::string event_to_string(FSMEvent event);

private:
    std::map<std::string, std::shared_ptr<BaseState>> states_;
    std::map<std::pair<std::string, FSMEvent>, std::string> transitions_;
    std::string current_state_;
    std::shared_ptr<spdlog::logger> logger_;
};
