// daemon/control_plane/fsm/state_init.cpp
#include "state_init.hpp"

namespace atrop::fsm {

InitState::InitState() {
    // Load node identity from config
    auto config = sdk::load_config("config.yaml");
    node_id_ = config["node"]["id"].as<std::string>();
}

FSMStateID InitState::id() const {
    return FSMStateID::INIT;
}

void InitState::enter() {
    ATROP_LOG_INFO("Entering INIT state");
    ATROP_LOG_INFO("Node ID: {}", node_id_);
    // Stub: Initialize identity, keys, session tracking
}

void InitState::exit() {
    ATROP_LOG_INFO("Exiting INIT state");
    // Stub: Cleanup temp buffers or flags if needed
}

FSMStateID InitState::handle_event(FSMEvent event) {
    if (event == FSMEvent::DiscoveryComplete) {
        ATROP_LOG_INFO("Trigger received: DiscoveryComplete");
        return FSMStateID::DISCOVERY;
    }
    return FSMStateID::INIT;
}

} // namespace atrop::fsm
