#include "state_correct.hpp"

namespace atrop::fsm {

CorrectState::CorrectState() {
    auto config = sdk::load_config("config.yaml");
    critical_mode_ = config["correction"]["critical_mode"].as<bool>();
}

FSMStateID CorrectState::id() const {
    return FSMStateID::CORRECT;
}

void CorrectState::enter() {
    LOG_INFO("Entering CORRECT state");
    LOG_INFO("Critical fallback mode: {}", critical_mode_);
}

void CorrectState::exit() {
    LOG_INFO("Exiting CORRECT state");
}

FSMStateID CorrectState::handle_event(FSMEvent event) {
    if (critical_mode_) {
        LOG_INFO("Critical fault → transition to EXIT");
        return FSMStateID::EXIT;
    }
    if (event == FSMEvent::InferenceReady) {
        LOG_INFO("Correction complete → retrying DECIDE");
        return FSMStateID::DECIDE;
    }
    return FSMStateID::CORRECT;
}

} // namespace atrop::fsm