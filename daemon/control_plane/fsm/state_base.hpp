#pragma once

#include "state_base.hpp"
#include <string>

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
