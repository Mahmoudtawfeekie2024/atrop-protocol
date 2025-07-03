#include "state_exit.hpp"

namespace atrop::fsm {

ExitState::ExitState() {
    auto config = sdk::load_config("config.yaml");
    secure_mode_ = config["exit"]["secure"].as<bool>();
}

FSMStateID ExitState::id() const {
    return FSMStateID::EXIT;
}

void ExitState::enter() {
    LOG_INFO("Entering EXIT state");
    LOG_INFO("Secure mode: {}", secure_mode_);
}

void ExitState::exit() {
    LOG_INFO("Exiting EXIT state (should not happen — terminal state)");
}

FSMStateID ExitState::handle_event(FSMEvent) {
    LOG_WARN("EXIT state is terminal — ignoring events");
    return FSMStateID::EXIT;
}

} // namespace atrop::fsm