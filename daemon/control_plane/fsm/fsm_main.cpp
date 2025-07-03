// daemon/control_plane/fsm/fsm_main.cpp
#include "fsm_engine.hpp"
#include "fsm_transitions.hpp"

// Temporary stubs (replace later)
#include <iostream>
using namespace atrop::fsm;

class InitState : public State {
public:
    FSMStateID id() const override { return FSMStateID::INIT; }
    void enter() override { std::cout << "[FSM] Enter INIT\n"; }
    void exit() override { std::cout << "[FSM] Exit INIT\n"; }
    FSMStateID handle_event(FSMEvent event) override {
        return (event == FSMEvent::DiscoveryComplete) ? FSMStateID::DISCOVERY : FSMStateID::INIT;
    }
};

class DiscoveryState : public State {
public:
    FSMStateID id() const override { return FSMStateID::DISCOVERY; }
    void enter() override { std::cout << "[FSM] Enter DISCOVERY\n"; }
    void exit() override { std::cout << "[FSM] Exit DISCOVERY\n"; }
    FSMStateID handle_event(FSMEvent event) override {
        return (event == FSMEvent::TrainingComplete) ? FSMStateID::LEARN : FSMStateID::DISCOVERY;
    }
};

int main() {
    FSMEngine engine;

    engine.register_state(std::make_shared<InitState>());
    engine.register_state(std::make_shared<DiscoveryState>());

    engine.set_initial(FSMStateID::INIT);
    engine.process_event(FSMEvent::DiscoveryComplete);
    engine.process_event(FSMEvent::TrainingComplete);

    return 0;
}
