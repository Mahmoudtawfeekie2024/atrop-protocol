// daemon/control_plane/fsm/fsm_engine.cpp
#include "fsm_engine.hpp"
#include "fsm_transitions.hpp"
#include <iostream>

namespace atrop::fsm {

FSMEngine::FSMEngine() = default;

void FSMEngine::register_state(std::shared_ptr<State> state) {
    state_map_[state->id()] = state;
}

void FSMEngine::set_initial(FSMStateID id) {
    current_state_ = state_map_.at(id);
    current_state_->enter();
}

void FSMEngine::process_event(FSMEvent event) {
    FSMStateID next_id = current_state_->handle_event(event);

    if (next_id != current_state_->id() &&
        is_valid_transition(current_state_->id(), next_id)) {
        current_state_->exit();
        current_state_ = state_map_.at(next_id);
        current_state_->enter();
    } else {
        std::cerr << "⚠️ Invalid FSM transition from "
                  << static_cast<int>(current_state_->id())
                  << " to " << static_cast<int>(next_id) << std::endl;
    }
}

} // namespace atrop::fsm
