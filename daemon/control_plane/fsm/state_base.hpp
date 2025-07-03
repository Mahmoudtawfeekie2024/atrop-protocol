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
    EXIT // <-- Add this line
};

enum class FSMEvent {
    // Define your event types here
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
