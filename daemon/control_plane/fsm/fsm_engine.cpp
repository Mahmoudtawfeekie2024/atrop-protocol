#include "fsm_engine.hpp"

FSMEngine::FSMEngine(std::shared_ptr<spdlog::logger> logger)
    : logger_(std::move(logger)), current_state_("") {}

void FSMEngine::register_state(const std::string& state_name, std::shared_ptr<BaseState> state) {
    states_[state_name] = std::move(state);
    if (logger_) {
        logger_->info("FSM: Registered state '{}'", state_name);
    }
}

void FSMEngine::add_transition(const std::string& from_state, FSMEvent event, const std::string& to_state) {
    transitions_[{from_state, event}] = to_state;
    if (logger_) {
        logger_->info("FSM: Added transition {} + {} -> {}", from_state, event_to_string(event), to_state);
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
    if (!current_state_.empty() && states_.count(current_state_)) {
        states_[current_state_]->on_exit();
    }
    current_state_ = state_name;
    if (logger_) {
        logger_->info("FSM: Transitioned to state '{}'", state_name);
    }
    states_[state_name]->on_enter();
    return true;
}

void FSMEngine::start(const std::string& initial_state) {
    if (!transition_to(initial_state)) {
        if (logger_) {
            logger_->error("FSM: Failed to start at state '{}'", initial_state);
        }
    }
}

void FSMEngine::handle_event(FSMEvent event) {
    std::string from = current_state_;
    auto key = std::make_pair(from, event);
    auto it = transitions_.find(key);
    if (it == transitions_.end()) {
        if (logger_) {
            logger_->error("FSM: Invalid transition: State='{}', Event='{}'", from, event_to_string(event));
        }
        return;
    }
    std::string to = it->second;
    if (logger_) {
        logger_->info("FSM: Handling event '{}' in state '{}', transitioning to '{}'", event_to_string(event), from, to);
    }
    transition_to(to);
}

std::string FSMEngine::current_state_name() const {
    return current_state_;
}

std::string FSMEngine::event_to_string(FSMEvent event) {
    switch (event) {
        case FSMEvent::RegistrationComplete: return "RegistrationComplete";
        case FSMEvent::NeighborsMapped: return "NeighborsMapped";
        case FSMEvent::TopologyStable: return "TopologyStable";
        case FSMEvent::PolicyApproved: return "PolicyApproved";
        case FSMEvent::ForwardingActive: return "ForwardingActive";
        case FSMEvent::TelemetryThreshold: return "TelemetryThreshold";
        case FSMEvent::ModelUpdated: return "ModelUpdated";
        case FSMEvent::AnomalyViolation: return "AnomalyViolation";
        case FSMEvent::FallbackRecovery: return "FallbackRecovery";
        case FSMEvent::CorrectionApplied: return "CorrectionApplied";
        case FSMEvent::TrustRevoked: return "TrustRevoked";
        case FSMEvent::NodeShutdown: return "NodeShutdown";
        case FSMEvent::ManualOverride: return "ManualOverride";
        case FSMEvent::ManualReset: return "ManualReset";
        default: return "Unknown";
    }
}
