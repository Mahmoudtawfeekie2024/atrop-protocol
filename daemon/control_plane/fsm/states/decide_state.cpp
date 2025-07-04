#include "decide_state.hpp"

DecideState::DecideState(std::shared_ptr<spdlog::logger> logger)
    : logger_(std::move(logger)) {}

void DecideState::on_enter() {
    if (logger_) {
        logger_->info("[DECIDE] Entering DECIDE state.");
    }
    // TODO: Add control plane route decision logic here (AI policy, predictive models)
}

void DecideState::on_exit() {
    if (logger_) {
        logger_->info("[DECIDE] Exiting DECIDE state.");
    }
    // TODO: Add cleanup logic here if needed
}
