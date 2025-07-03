#include "state_feedback.hpp"

namespace atrop::fsm {

FeedbackState::FeedbackState() {
    auto config = sdk::load_config("config.yaml");
    confidence_threshold_ = config["feedback"]["min_confidence"].as<double>();
    feedback_enabled_ = config["feedback"]["enabled"].as<bool>();
}

FSMStateID FeedbackState::id() const {
    return FSMStateID::FEEDBACK;
}

void FeedbackState::enter() {
    LOG_INFO("Entering FEEDBACK state");
    LOG_INFO("Feedback enabled: {}, Min confidence: {}", feedback_enabled_, confidence_threshold_);

    // 🔧 Stub: Trigger learning or intent revision
    LOG_DEBUG("[STUB] Performing model feedback evaluation");
}

void FeedbackState::exit() {
    LOG_INFO("Exiting FEEDBACK state");
}

FSMStateID FeedbackState::handle_event(FSMEvent event) {
    if (event == FSMEvent::InferenceReady) {
        LOG_INFO("Feedback triggers new inference → transition to DECIDE");
        return FSMStateID::DECIDE;
    }
    if (event == FSMEvent::AnomalyDetected) {
        LOG_INFO("Feedback detected SLA/anomaly → transition to CORRECT");
        return FSMStateID::CORRECT;
    }
    return FSMStateID::FEEDBACK;
}

} // namespace atrop::fsm