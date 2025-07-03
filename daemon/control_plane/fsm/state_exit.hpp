// daemon/control_plane/fsm/state_exit.hpp
#pragma once

#include "state_base.hpp"
#include "../common/logger.hpp"
#include "sdk/c++/config_loader.hpp"

namespace atrop::fsm {

class ExitState : public State {
public:
    ExitState();
    FSMStateID id() const override;
    void enter() override;
    void exit() override;
    FSMStateID handle_event(FSMEvent event) override;

private:
    bool secure_mode_;
};

} // namespace atrop::fsm
