#include "enforce_state.hpp"

EnforceState::EnforceState(std::shared_ptr<spdlog::logger> logger)
    : logger_(std::move(logger)) {}

void EnforceState::on_enter() {
    if (logger_) {
        logger_->info("[ENFORCE] Entering ENFORCE state.");
    }
    // TODO: Add logic to implement forwarding paths and policy enforcement here
}

void EnforceState::on_exit() {
    if (logger_) {
        logger_->info("[ENFORCE] Exiting ENFORCE state.");
    }
    // TODO: Add cleanup logic here if needed
}
