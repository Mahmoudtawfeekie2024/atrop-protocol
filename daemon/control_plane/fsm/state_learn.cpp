#include "state_learn.hpp"

namespace atrop::fsm {

LearnState::LearnState() {
    auto config = sdk::load_config("config.yaml");
    model_type_ = config["ml"]["model_type"].as<std::string>();
    pretrained_ = config["ml"]["use_pretrained"].as<bool>();
}

FSMStateID LearnState::id() const {
    return FSMStateID::LEARN;
}

void LearnState::enter() {
    LOG_INFO("Entering LEARN state");
    LOG_INFO("Model type: {}, pretrained: {}", model_type_, pretrained_);
}

void LearnState::exit() {
    LOG_INFO("Exiting LEARN state");
}

FSMStateID LearnState::handle_event(FSMEvent event) {
    if (event == FSMEvent::InferenceReady) {
        LOG_INFO("Trigger received: InferenceReady → transition to DECIDE");
        return FSMStateID::DECIDE;
    }
    return FSMStateID::LEARN;
}

} // namespace atrop::fsm