#pragma once

#include <string>

// Abstract base class for all FSM states
class BaseState {
public:
    virtual ~BaseState() = default;

    // Called when entering the state
    virtual void on_enter() = 0;

    // Called when exiting the state
    virtual void on_exit() = 0;

    // Returns the name of the state
    virtual std::string name() const = 0;
};
