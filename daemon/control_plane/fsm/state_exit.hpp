#pragma once
#include "state_base.hpp"

namespace atrop::fsm {

class ExitState : public State {
public:
    ExitState(); // Add this if you have a constructor in the cpp
    FSMStateID id() const override;
    void enter() override;
    void exit() override;
    FSMStateID handle_event(FSMEvent event) override;
private:
    bool secure_mode_ = false; // Add this if you use it in your cpp
};

} // namespace atrop::fsm
