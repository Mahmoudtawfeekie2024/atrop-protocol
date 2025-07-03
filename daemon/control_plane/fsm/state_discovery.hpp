// daemon/control_plane/fsm/state_discovery.hpp
#pragma once

#include "state_base.hpp"
#include "../common/logger.hpp"
#include "sdk/c++/config_loader.hpp"

namespace atrop::fsm {

class DiscoveryState : public State {
public:
    DiscoveryState();
    FSMStateID id() const override;
    void enter() override;
    void exit() override;
    FSMStateID handle_event(FSMEvent event) override;

private:
    std::string discovery_method_;
};

} // namespace atrop::fsm
