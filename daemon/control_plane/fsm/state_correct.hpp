// daemon/control_plane/fsm/state_correct.hpp
#pragma once

#include "state_base.hpp"
#include "logger.hpp"
#include "sdk/c++/config_loader.hpp"

namespace atrop::fsm {

class CorrectState : public State {
public:
    CorrectState();
    FSMStateID id() const override;
    void enter() override;
    void exit() override;
    FSMStateID handle_event(FSMEvent event) override;

private:
    bool critical_mode_;
};

} // namespace atrop::fsm
