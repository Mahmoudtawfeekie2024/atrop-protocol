#include "state_learn.hpp"
#include "sdk/c++/config_loader.hpp"

namespace atrop::fsm {

LearnState::LearnState() {
    auto config = sdk::config::ConfigLoader::load("config.yaml");
    model_type_ = std::get<std::string>(config.at("ml.model_type"));
    pretrained_ = std::get<bool>(config.at("ml.use_pretrained"));
}

FSMStateID LearnState::id() const {
    return FSMStateID::LEARN;
}

void LearnState::enter() {
    LOG_INFO("Entering LEARN state");
    LOG_INFO("Model type: {}, Use pretrained: {}", model_type_, pretrained_);

    // 🔧 Stub: Model training or loading
    LOG_DEBUG("[STUB] Training or loading ML model");
}

void LearnState::exit() {
    LOG_INFO("Exiting LEARN state");
}

FSMStateID LearnState::handle_event(FSMEvent event) {
    if (event == FSMEvent::TrainingComplete) {
        LOG_INFO("Training complete → transition to DECIDE");
        return FSMStateID::DECIDE;
    }
    return FSMStateID::LEARN;
}

} // namespace atrop::fsm
