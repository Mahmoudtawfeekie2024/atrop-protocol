// daemon/control_plane/fsm/state_exit.cpp
#include "state_exit.hpp"

namespace atrop::fsm {

ExitState::ExitState() {
    auto config = sdk::load_config("config.yaml");
    secure_mode_ = config["exit"]["secure"].as<bool>();  // true = isolate node on shutdown
}

FSMStateID ExitState::id() const {
    return FSMStateID::EXIT;
}

void ExitState::enter() {
    ATROP_LOG_INFO("Entering EXIT state");
    ATROP_LOG_INFO("Secure mode: {}", secure_mode_);

    // TODO: Release resources, flush logs, signal control shutdown
    // Optionally trigger quarantine or node-level isolation
}

void ExitState::exit() {
    ATROP_LOG_INFO("Exiting EXIT state (should not happen — terminal state)");
}

FSMStateID ExitState::handle_event(FSMEvent) {
    // Terminal state — no transitions allowed
    ATROP_LOG_WARN("EXIT state is terminal — ignoring events");
    return FSMStateID::EXIT;
}

} // namespace atrop::fsm
