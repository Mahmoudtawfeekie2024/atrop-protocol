#include "observe_state.hpp"

ObserveState::ObserveState(std::shared_ptr<spdlog::logger> logger)
    : logger_(std::move(logger)) {}

void ObserveState::on_enter() {
    if (logger_) {
        logger_->info("[OBSERVE] Entering OBSERVE state.");
    }
    // TODO: Add telemetry collection and observation logic here
}

void ObserveState::on_exit() {
    if (logger_) {
        logger_->info("[OBSERVE] Exiting OBSERVE state.");
    }
    // TODO: Add cleanup logic here if needed
}
