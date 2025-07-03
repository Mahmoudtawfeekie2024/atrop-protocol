#include "state_exit.hpp"
#include "sdk/c++/config_loader.hpp"

namespace atrop::fsm {

ExitState::ExitState() {
    auto config = sdk::config::ConfigLoader::load("config.yaml");
    secure_mode_ = std::get<bool>(config.at("exit.secure"));
}

FSMStateID ExitState::id() const {
    return FSMStateID::EXIT;
}

void ExitState::enter() {
    LOG_INFO("Entering EXIT state");
    LOG_INFO("Secure mode: {}", secure_mode_);

    // 🔧 Stub: Final secure shutdown / cleanup
    LOG_DEBUG("[STUB] Flushing telemetry, terminating sessions, locking interfaces");
}

void ExitState::exit() {
    LOG_INFO("Exiting EXIT state (should not happen — terminal state)");
}

FSMStateID ExitState::handle_event(FSMEvent) {
    LOG_WARN("EXIT state is terminal — ignoring events");
    return FSMStateID::EXIT;
}

} // namespace atrop::fsm
