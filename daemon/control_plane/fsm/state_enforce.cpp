#include "state_enforce.hpp"
#include "sdk/c++/config_loader.hpp"

namespace atrop::fsm {

EnforceState::EnforceState() {
    auto config = sdk::config::ConfigLoader::load("config.yaml");
    enforce_mode_ = std::get<std::string>(config.at("enforcement.mode"));
}

FSMStateID EnforceState::id() const {
    return FSMStateID::ENFORCE;
}

void EnforceState::enter() {
    LOG_INFO("Entering ENFORCE state");
    LOG_INFO("Enforcement mode: {}", enforce_mode_);

    // 🔧 Stub: Apply enforcement policy
    LOG_DEBUG("[STUB] Applying enforcement policy");
}

void EnforceState::exit() {
    LOG_INFO("Exiting ENFORCE state");
}

FSMStateID EnforceState::handle_event(FSMEvent event) {
    // Use a valid event here. For example, if the next state is triggered by "PolicyApplied":
    if (event == FSMEvent::PolicyApplied) {
        LOG_INFO("Policy applied → transition to OBSERVE");
        return FSMStateID::OBSERVE;
    }
    return FSMStateID::ENFORCE;
}

} // namespace atrop::fsm
