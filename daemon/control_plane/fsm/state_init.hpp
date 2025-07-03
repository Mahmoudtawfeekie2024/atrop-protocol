// daemon/control_plane/fsm/state_init.hpp
#pragma once

#include "state_base.hpp"
#include "../common/logger.hpp"
#include "sdk/c++/config_loader.hpp"

namespace atrop::fsm {

class InitState : public State {
public:
    InitState();
    FSMStateID id() const override;
    void enter() override;
    void exit() override;
    FSMStateID handle_event(FSMEvent event) override;

private:
    std::string node_id_;
};

} // namespace atrop::fsm
