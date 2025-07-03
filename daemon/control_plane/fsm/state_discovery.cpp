// daemon/control_plane/fsm/state_discovery.cpp
#include "state_discovery.hpp"

namespace atrop::fsm {

DiscoveryState::DiscoveryState() {
    auto config = sdk::load_config("config.yaml");
    discovery_method_ = config["discovery"]["method"].as<std::string>();  // e.g., "passive", "active"
}

FSMStateID DiscoveryState::id() const {
    return FSMStateID::DISCOVERY;
}

void DiscoveryState::enter() {
    ATROP_LOG_INFO("Entering DISCOVERY state");
    ATROP_LOG_INFO("Discovery method: {}", discovery_method_);

    // TODO: Neighbor + ATZ discovery logic here
    // e.g., multicast probes, listening to LLDP or ATROP Hello
}

void DiscoveryState::exit() {
    ATROP_LOG_INFO("Exiting DISCOVERY state");
    // Optional cleanup if needed
}

FSMStateID DiscoveryState::handle_event(FSMEvent event) {
    if (event == FSMEvent::TrainingComplete) {
        ATROP_LOG_INFO("Trigger received: TrainingComplete → transition to LEARN");
        return FSMStateID::LEARN;
    }
    return FSMStateID::DISCOVERY;
}

} // namespace atrop::fsm
