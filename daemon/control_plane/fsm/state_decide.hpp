// daemon/control_plane/fsm/state_decide.hpp
#pragma once

#include "state_base.hpp"
#include "logger.hpp"
#include "sdk/c++/config_loader.hpp"

namespace atrop::fsm {

class DecideState : public State {
public:
    DecideState();
    FSMStateID id() const override;
    void enter() override;
    void exit() override;
    FSMStateID handle_event(FSMEvent event) override;

private:
    std::string inference_mode_;
    std::string policy_profile_;
};

} // namespace atrop::fsm
