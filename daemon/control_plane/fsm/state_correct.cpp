// daemon/control_plane/fsm/state_correct.cpp
#include "state_correct.hpp"

namespace atrop::fsm {

CorrectState::CorrectState() {
    auto config = sdk::load_config("config.yaml");
    critical_mode_ = config["correction"]["critical_mode"].as<bool>();  // e.g., true = force EXIT
}

FSMStateID CorrectState::id() const {
    return FSMStateID::CORRECT;
}

void CorrectState::enter() {
    ATROP_LOG_INFO("Entering CORRECT state");
    ATROP_LOG_INFO("Critical fallback mode: {}", critical_mode_);

    // TODO: Launch fallback mechanism (e.g., reroute, isolate path, re-learn)
    // Could include: state rollback, topology reevaluation, zone detachment
}

void CorrectState::exit() {
    ATROP_LOG_INFO("Exiting CORRECT state");
}

FSMStateID CorrectState::handle_event(FSMEvent event) {
    if (critical_mode_) {
        ATROP_LOG_INFO("Critical fault → transition to EXIT");
        return FSMStateID::EXIT;
    }

    if (event == FSMEvent::InferenceReady) {
        ATROP_LOG_INFO("Correction complete → retrying DECIDE");
        return FSMStateID::DECIDE;
    }

    return FSMStateID::CORRECT;
}

} // namespace atrop::fsm
