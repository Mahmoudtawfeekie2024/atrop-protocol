// daemon/control_plane/fsm/state_enforce.cpp
#include "state_enforce.hpp"

namespace atrop::fsm {

EnforceState::EnforceState() {
    auto config = sdk::load_config("config.yaml");
    enforce_mode_ = config["enforcement"]["mode"].as<std::string>(); // e.g., "push", "advisory"
}

FSMStateID EnforceState::id() const {
    return FSMStateID::ENFORCE;
}

void EnforceState::enter() {
    ATROP_LOG_INFO("Entering ENFORCE state");
    ATROP_LOG_INFO("Enforcement mode: {}", enforce_mode_);

    // TODO: Push AI-selected routes into RIB/FIB
    // Interface with dataplane, policy hooks, or FIB agent
    ATROP_LOG_INFO("Applying routing decisions to system...");
}

void EnforceState::exit() {
    ATROP_LOG_INFO("Exiting ENFORCE state");
}

FSMStateID EnforceState::handle_event(FSMEvent event) {
    if (event == FSMEvent::None) {
        ATROP_LOG_INFO("Transitioning from ENFORCE → OBSERVE");
        return FSMStateID::OBSERVE;
    }
    return FSMStateID::ENFORCE;
}

} // namespace atrop::fsm
