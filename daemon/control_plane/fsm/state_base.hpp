// daemon/control_plane/fsm/state_base.hpp
#pragma once

#include <string>

namespace atrop::fsm {

enum class FSMEvent {
    None,
    DiscoveryComplete,
    TrainingComplete,
    InferenceReady,
    AnomalyDetected,
    ShutdownRequested
};

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

class State {
public:
    virtual ~State() = default;

    virtual FSMStateID id() const = 0;
    virtual void enter() = 0;
    virtual void exit() = 0;
    virtual FSMStateID handle_event(FSMEvent event) = 0;
};

} // namespace atrop::fsm
