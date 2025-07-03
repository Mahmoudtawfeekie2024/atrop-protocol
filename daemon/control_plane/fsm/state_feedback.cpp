// daemon/control_plane/fsm/state_feedback.cpp
#include "state_feedback.hpp"

namespace atrop::fsm {

FeedbackState::FeedbackState() {
    auto config = sdk::load_config("config.yaml");
    confidence_threshold_ = config["feedback"]["min_confidence"].as<double>();  // e.g., 0.9
    feedback_enabled_ = config["feedback"]["enabled"].as<bool>();
}

FSMStateID FeedbackState::id() const {
    return FSMStateID::FEEDBACK;
}

void FeedbackState::enter() {
    ATROP_LOG_INFO("Entering FEEDBACK state");
    ATROP_LOG_INFO("Feedback enabled: {}, Min confidence: {}", feedback_enabled_, confidence_threshold_);

    // TODO: Evaluate AI scores, model outputs, policy deviation
    // Prepare retraining or signal to DECIDE
}

void FeedbackState::exit() {
    ATROP_LOG_INFO("Exiting FEEDBACK state");
}

FSMStateID FeedbackState::handle_event(FSMEvent event) {
    if (event == FSMEvent::InferenceReady) {
        ATROP_LOG_INFO("Feedback triggers new inference → transition to DECIDE");
        return FSMStateID::DECIDE;
    }
    if (event == FSMEvent::AnomalyDetected) {
        ATROP_LOG_INFO("Feedback detected SLA/anomaly → transition to CORRECT");
        return FSMStateID::CORRECT;
    }
    return FSMStateID::FEEDBACK;
}

} // namespace atrop::fsm
