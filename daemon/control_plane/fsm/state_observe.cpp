#include "state_observe.hpp"

namespace atrop::fsm {

ObserveState::ObserveState() {
    auto config = sdk::load_config("config.yaml");
    anomaly_threshold_ = config["observe"]["anomaly_threshold"].as<double>();
    telemetry_enabled_ = config["observe"]["enabled"].as<bool>();
}

FSMStateID ObserveState::id() const {
    return FSMStateID::OBSERVE;
}

void ObserveState::enter() {
    LOG_INFO("Entering OBSERVE state");
    LOG_INFO("Telemetry enabled: {}, Anomaly threshold: {}", telemetry_enabled_, anomaly_threshold_);

    // 🔧 Stub: Start telemetry and anomaly monitors
    LOG_DEBUG("[STUB] Activating real-time telemetry watchers and analytics");
}

void ObserveState::exit() {
    LOG_INFO("Exiting OBSERVE state");
}

FSMStateID ObserveState::handle_event(FSMEvent event) {
    if (event == FSMEvent::AnomalyDetected) {
        LOG_INFO("Anomaly detected → transition to CORRECT");
        return FSMStateID::CORRECT;
    }
    if (event == FSMEvent::None) {
        LOG_INFO("Normal telemetry loop → transition to FEEDBACK");
        return FSMStateID::FEEDBACK;
    }
    return FSMStateID::OBSERVE;
}

} // namespace atrop::fsm