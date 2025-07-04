#include "correct_state.hpp"

CorrectState::CorrectState(std::shared_ptr<spdlog::logger> logger)
    : logger_(std::move(logger)) {}

void CorrectState::on_enter() {
    if (logger_) {
        logger_->info("[CORRECT] Entering CORRECT state.");
    }
    // TODO: Add anomaly correction, reroute, or isolation logic here
}

void CorrectState::on_exit() {
    if (logger_) {
        logger_->info("[CORRECT] Exiting CORRECT state.");
    }
    // TODO: Add cleanup logic here if needed
}
