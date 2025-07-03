// daemon/control_plane/fsm/state_observe.hpp
#pragma once

#include "state_base.hpp"
#include "logger.hpp"
#include "../common/logger.hpp"

namespace atrop::fsm {

class ObserveState : public State {
public:
    ObserveState();
    FSMStateID id() const override;
    void enter() override;
    void exit() override;
    FSMStateID handle_event(FSMEvent event) override;

private:
    double anomaly_threshold_;
    bool telemetry_enabled_;
};

} // namespace atrop::fsm
