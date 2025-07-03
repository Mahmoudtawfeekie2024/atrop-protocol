#include "state_decide.hpp"

namespace atrop::fsm {

DecideState::DecideState() {
    auto config = sdk::load_config("config.yaml");
    inference_mode_ = config["ai"]["mode"].as<std::string>();
    policy_profile_ = config["policy"]["profile"].as<std::string>();
}

FSMStateID DecideState::id() const {
    return FSMStateID::DECIDE;
}

void DecideState::enter() {
    LOG_INFO("Entering DECIDE state");
    LOG_INFO("AI mode: {}, Policy profile: {}", inference_mode_, policy_profile_);
}

void DecideState::exit() {
    LOG_INFO("Exiting DECIDE state");
}

FSMStateID DecideState::handle_event(FSMEvent event) {
    if (event == FSMEvent::InferenceReady) {
        LOG_INFO("Trigger received: InferenceReady → transition to ENFORCE");
        return FSMStateID::ENFORCE;
    }
    return FSMStateID::DECIDE;
}

} // namespace atrop::fsm