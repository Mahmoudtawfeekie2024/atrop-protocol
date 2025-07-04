#include "fsm_engine.hpp"

FSMEngine::FSMEngine(std::shared_ptr<spdlog::logger> logger)
    : logger_(std::move(logger)), current_state_(nullptr) {}

void FSMEngine::register_state(const std::string& state_name, std::shared_ptr<BaseState> state) {
    states_[state_name] = std::move(state);
    if (logger_) {
        logger_->info("FSM: Registered state '{}'", state_name);
    }
}

bool FSMEngine::transition_to(const std::string& state_name) {
    auto it = states_.find(state_name);
    if (it == states_.end()) {
        if (logger_) {
            logger_->error("FSM: State '{}' not found!", state_name);
        }
        return false;
    }
    if (current_state_) {
        current_state_->on_exit();
    }
    current_state_ = it->second;
    if (logger_) {
        logger_->info("FSM: Transitioned to state '{}'", state_name);
    }
    current_state_->on_enter();
    return true;
}

std::string FSMEngine::current_state_name() const {
    return current_state_ ? current_state_->name() : "NONE";
}

void FSMEngine::start(const std::string& initial_state) {
    if (!transition_to(initial_state)) {
        if (logger_) {
            logger_->error("FSM: Failed to start at state '{}'", initial_state);
        }
    }
}
