#include "state_decide.hpp"
#include "sdk/c++/config_loader.hpp"

namespace atrop::fsm {

DecideState::DecideState() {
    auto config = sdk::config::ConfigLoader::load("config.yaml");
    inference_mode_ = std::get<std::string>(config.at("ai.mode"));
    policy_profile_ = std::get<std::string>(config.at("policy.profile"));
}

FSMStateID DecideState::id() const {
    return FSMStateID::DECIDE;
}

void DecideState::enter() {
    LOG_INFO("Entering DECIDE state");
    LOG_INFO("AI mode: {}, Policy profile: {}", inference_mode_, policy_profile_);

    // 🔧 Stub: SLA and policy confidence check
    LOG_DEBUG("[STUB] Verifying SLA metrics and AI route confidence");
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
