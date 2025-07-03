#pragma once
#include "state_base.hpp"

namespace atrop::fsm {

class ExitState : public State {
public:
    FSMStateID id() const override;
    void enter() override;
    void exit() override;
    FSMStateID handle_event(FSMEvent event) override;
};

} // namespace atrop::fsm
