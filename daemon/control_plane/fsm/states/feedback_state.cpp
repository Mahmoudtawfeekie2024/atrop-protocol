#include "feedback_state.hpp"

FeedbackState::FeedbackState(std::shared_ptr<spdlog::logger> logger)
    : logger_(std::move(logger)) {}

void FeedbackState::on_enter() {
    if (logger_) {
        logger_->info("[FEEDBACK] Entering FEEDBACK state.");
    }
    // TODO: Add AI model retraining or adjustment logic here
}

void FeedbackState::on_exit() {
    if (logger_) {
        logger_->info("[FEEDBACK] Exiting FEEDBACK state.");
    }
    // TODO: Add cleanup logic here if needed
}
