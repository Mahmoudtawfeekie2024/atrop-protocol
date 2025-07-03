// daemon/control_plane/fsm/state_learn.hpp
#pragma once

#include "state_base.hpp"
#include "../common/logger.hpp"
#include "sdk/c++/config_loader.hpp"

namespace atrop::fsm {

class LearnState : public State {
public:
    LearnState();
    FSMStateID id() const override;
    void enter() override;
    void exit() override;
    FSMStateID handle_event(FSMEvent event) override;

private:
    std::string model_type_;
    bool pretrained_;
};

} // namespace atrop::fsm
