// daemon/control_plane/fsm/state_feedback.hpp
#pragma once

#include "state_base.hpp"
#include "logger.hpp"
#include "sdk/c++/config_loader.hpp"

namespace atrop::fsm {

class FeedbackState : public State {
public:
    FeedbackState();
    FSMStateID id() const override;
    void enter() override;
    void exit() override;
    FSMStateID handle_event(FSMEvent event) override;

private:
    double confidence_threshold_;
    bool feedback_enabled_;
};

} // namespace atrop::fsm
