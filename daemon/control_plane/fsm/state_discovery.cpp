#include "state_discovery.hpp"
#include "sdk/c++/config_loader.hpp"

namespace atrop::fsm {

DiscoveryState::DiscoveryState() {
    auto config = sdk::config::ConfigLoader::load("config.yaml");
    discovery_method_ = std::get<std::string>(config.at("discovery.method"));
}

FSMStateID DiscoveryState::id() const {
    return FSMStateID::DISCOVERY;
}

void DiscoveryState::enter() {
    LOG_INFO("Entering DISCOVERY state");
    LOG_INFO("Discovery method: {}", discovery_method_);

    // 🔧 Stub: Start discovery telemetry
    LOG_DEBUG("[STUB] Enabling passive/active discovery probes");
}

void DiscoveryState::exit() {
    LOG_INFO("Exiting DISCOVERY state");
}

FSMStateID DiscoveryState::handle_event(FSMEvent event) {
    if (event == FSMEvent::TrainingComplete) {
        LOG_INFO("Trigger received: TrainingComplete");
        return FSMStateID::LEARN;
    }
    return FSMStateID::DISCOVERY;
}

} // namespace atrop::fsm
