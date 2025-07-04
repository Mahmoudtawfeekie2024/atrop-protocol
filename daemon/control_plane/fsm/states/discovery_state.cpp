#include "discovery_state.hpp"

DiscoveryState::DiscoveryState(std::shared_ptr<spdlog::logger> logger)
    : logger_(std::move(logger)) {}

void DiscoveryState::on_enter() {
    if (logger_) {
        logger_->info("[DISCOVERY] Entering DISCOVERY state.");
    }
    // TODO: Add neighbor discovery and ATZ boundary mapping logic here
}

void DiscoveryState::on_exit() {
    if (logger_) {
        logger_->info("[DISCOVERY] Exiting DISCOVERY state.");
    }
    // TODO: Add cleanup logic here if needed
}
