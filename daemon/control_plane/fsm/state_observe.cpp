// daemon/control_plane/fsm/state_observe.cpp
#include "state_observe.hpp"

namespace atrop::fsm {

ObserveState::ObserveState() {
    auto config = sdk::load_config("config.yaml");
    anomaly_threshold_ = config["observe"]["anomaly_threshold"].as<double>();  // e.g., 0.8
    telemetry_enabled_ = config["observe"]["enabled"].as<bool>();              // true / false
}

FSMStateID ObserveState::id() const {
    return FSMStateID::OBSERVE;
}

void ObserveState::enter() {
    ATROP_LOG_INFO("Entering OBSERVE state");
    ATROP_LOG_INFO("Telemetry enabled: {}, Anomaly threshold: {}", telemetry_enabled_, anomaly_threshold_);

    // TODO: Collect real-time telemetry (FIF, RTT, utilization)
    // Feed values to ML/monitoring buffers
}

void ObserveState::exit() {
    ATROP_LOG_INFO("Exiting OBSERVE state");
}

FSMStateID ObserveState::handle_event(FSMEvent event) {
    if (event == FSMEvent::AnomalyDetected) {
        ATROP_LOG_INFO("Anomaly detected → transition to CORRECT");
        return FSMStateID::CORRECT;
    }
    if (event == FSMEvent::None) {
        ATROP_LOG_INFO("Normal telemetry loop → transition to FEEDBACK");
        return FSMStateID::FEEDBACK;
    }
    return FSMStateID::OBSERVE;
}

} // namespace atrop::fsm
