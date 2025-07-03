// daemon/control_plane/fsm/state_learn.cpp
#include "state_learn.hpp"

namespace atrop::fsm {

LearnState::LearnState() {
    auto config = sdk::load_config("config.yaml");
    model_type_ = config["ml"]["model_type"].as<std::string>();       // e.g., "GNN", "DNN", "RL"
    pretrained_ = config["ml"]["use_pretrained"].as<bool>();          // true / false
}

FSMStateID LearnState::id() const {
    return FSMStateID::LEARN;
}

void LearnState::enter() {
    ATROP_LOG_INFO("Entering LEARN state");
    ATROP_LOG_INFO("Model type: {}, pretrained: {}", model_type_, pretrained_);

    // TODO: Actual training/inference integration
    // e.g., prepare topology vectors (PIV/NIV), call training module
    if (pretrained_) {
        ATROP_LOG_INFO("Loading pretrained model...");
    } else {
        ATROP_LOG_INFO("Training model on topology data...");
    }
}

void LearnState::exit() {
    ATROP_LOG_INFO("Exiting LEARN state");
    // Optionally save temporary artifacts or logs
}

FSMStateID LearnState::handle_event(FSMEvent event) {
    if (event == FSMEvent::InferenceReady) {
        ATROP_LOG_INFO("Trigger received: InferenceReady → transition to DECIDE");
        return FSMStateID::DECIDE;
    }
    return FSMStateID::LEARN;
}

} // namespace atrop::fsm
