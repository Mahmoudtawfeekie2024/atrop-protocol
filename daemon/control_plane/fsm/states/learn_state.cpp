#include "learn_state.hpp"

LearnState::LearnState(std::shared_ptr<spdlog::logger> logger)
    : logger_(std::move(logger)) {}

void LearnState::on_enter() {
    if (logger_) {
        logger_->info("[LEARN] Entering LEARN state.");
    }
    // TODO: Add AI topology modeling and ML flow analysis logic here
}

void LearnState::on_exit() {
    if (logger_) {
        logger_->info("[LEARN] Exiting LEARN state.");
    }
    // TODO: Add cleanup logic here if needed
}
