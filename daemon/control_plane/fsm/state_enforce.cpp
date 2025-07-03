#include "state_enforce.hpp"

namespace atrop::fsm {

EnforceState::EnforceState() {
    auto config = sdk::load_config("config.yaml");
    enforce_mode_ = config["enforcement"]["mode"].as<std::string>();
}

FSMStateID EnforceState::id() const {
    return FSMStateID::ENFORCE;
}

void EnforceState::enter() {
    LOG_INFO("Entering ENFORCE state");
    LOG_INFO("Enforcement mode: {}", enforce_mode_);
}

void EnforceState::exit() {
    LOG_INFO("Exiting ENFORCE state");
}

FSMStateID EnforceState::handle_event(FSMEvent event) {
    if (event == FSMEvent::None) {
        LOG_INFO("Transitioning from ENFORCE → OBSERVE");
        return FSMStateID::OBSERVE;
    }
    return FSMStateID::ENFORCE;
}

} // namespace atrop::fsm