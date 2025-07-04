#include "exit_state.hpp"

ExitState::ExitState(std::shared_ptr<spdlog::logger> logger)
    : logger_(std::move(logger)) {}

void ExitState::on_enter() {
    if (logger_) {
        logger_->info("[EXIT] Entering EXIT state.");
    }
    // TODO: Add logic for graceful shutdown, state export, or cleanup here
}

void ExitState::on_exit() {
    if (logger_) {
        logger_->info("[EXIT] Exiting EXIT state.");
    }
    // TODO: Add any final cleanup logic here if needed
}
