#include "state_exit.hpp"
#include "common/logger.hpp" // Adjust path as needed

using namespace atrop::fsm;

ExitState::ExitState() : secure_mode_(false) {}

FSMStateID ExitState::id() const {
    return FSMStateID::EXIT;
}

void ExitState::enter() {
    LOG_INFO("Entering EXIT state");
    LOG_INFO("Secure mode: {}", secure_mode_);
    LOG_DEBUG("[STUB] Flushing telemetry, terminating sessions, locking interfaces");
}

void ExitState::exit() {
    LOG_INFO("Exiting EXIT state (should not happen — terminal state)");
}

FSMStateID ExitState::handle_event(FSMEvent) {
    LOG_WARN("EXIT state is terminal — ignoring events");
    return FSMStateID::EXIT;
}
