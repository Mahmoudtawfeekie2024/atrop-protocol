// daemon/control_plane/fsm/state_enforce.hpp
#pragma once

#include "state_base.hpp"
#include "logger.hpp"
#include "sdk/c++/config_loader.hpp"

namespace atrop::fsm {

class EnforceState : public State {
public:
    EnforceState();
    FSMStateID id() const override;
    void enter() override;
    void exit() override;
    FSMStateID handle_event(FSMEvent event) override;

private:
    std::string enforce_mode_;
};

} // namespace atrop::fsm
