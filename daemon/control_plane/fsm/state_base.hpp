#pragma once

namespace atrop::fsm {

enum class FSMStateID {
    INIT,
    DISCOVERY,
    LEARN,
    DECIDE,
    ENFORCE,
    OBSERVE,
    FEEDBACK,
    CORRECT,
    EXIT
};

enum class FSMEvent {
    None,
    DiscoveryComplete,
    TrainingComplete,
    // Add other events as needed
};

class State {
public:
    virtual FSMStateID id() const = 0;
    virtual void enter() = 0;
    virtual void exit() = 0;
    virtual FSMStateID handle_event(FSMEvent event) = 0;
    virtual ~State() = default;
};

} // namespace atrop::fsm
