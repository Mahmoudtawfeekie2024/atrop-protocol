// daemon/control_plane/fsm/state_decide.cpp
#include "state_decide.hpp"

namespace atrop::fsm {

DecideState::DecideState() {
    auto config = sdk::load_config("config.yaml");
    inference_mode_ = config["ai"]["mode"].as<std::string>();              // e.g., "deterministic", "probabilistic"
    policy_profile_ = config["policy"]["profile"].as<std::string>();       // e.g., "default", "sla-aware", etc.
}

FSMStateID DecideState::id() const {
    return FSMStateID::DECIDE;
}

void DecideState::enter() {
    ATROP_LOG_INFO("Entering DECIDE state");
    ATROP_LOG_INFO("AI mode: {}, Policy profile: {}", inference_mode_, policy_profile_);

    // TODO: Call AI model inference with PIV/NIV + intent profile
    // Output routing decisions, best paths, scoring info
    ATROP_LOG_INFO("Performing route selection based on inference...");
}

void DecideState::exit() {
    ATROP_LOG_INFO("Exiting DECIDE state");
    // Optional: clear inference buffers or logs
}

FSMStateID DecideState::handle_event(FSMEvent event) {
    if (event == FSMEvent::InferenceReady) {
        ATROP_LOG_INFO("Trigger received: InferenceReady → transition to ENFORCE");
        return FSMStateID::ENFORCE;
    }
    return FSMStateID::DECIDE;
}

} // namespace atrop::fsm
