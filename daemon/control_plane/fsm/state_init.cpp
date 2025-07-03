#include "state_init.hpp"

namespace atrop::fsm {

InitState::InitState() {
    auto config = sdk::load_config("config.yaml");
    node_id_ = config["node"]["id"].as<std::string>();
}

FSMStateID InitState::id() const {
    return FSMStateID::INIT;
}

void InitState::enter() {
    LOG_INFO("Entering INIT state");
    LOG_INFO("Node ID: {}", node_id_);
}

void InitState::exit() {
    LOG_INFO("Exiting INIT state");
}

FSMStateID InitState::handle_event(FSMEvent event) {
    if (event == FSMEvent::DiscoveryComplete) {
        LOG_INFO("Trigger received: DiscoveryComplete");
        return FSMStateID::DISCOVERY;
    }
    return FSMStateID::INIT;
}

} // namespace atrop::fsm