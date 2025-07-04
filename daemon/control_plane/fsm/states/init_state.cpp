#include "init_state.hpp"

InitState::InitState(std::shared_ptr<spdlog::logger> logger)
    : logger_(std::move(logger)) {}

void InitState::on_enter() {
    if (logger_) {
        logger_->info("[INIT] Entering INIT state.");
    }
    // TODO: Add initialization logic here (e.g., identity generation, config checks)
}

void InitState::on_exit() {
    if (logger_) {
        logger_->info("[INIT] Exiting INIT state.");
    }
    // TODO: Add cleanup logic here if needed
}
