// daemon/control_plane/fsm/fsm_engine.hpp
#pragma once

#include "state_base.hpp"
#include <memory>
#include <map>

namespace atrop::fsm {

class FSMEngine {
public:
    FSMEngine();
    void register_state(std::shared_ptr<State> state);
    void set_initial(FSMStateID id);
    void process_event(FSMEvent event);

private:
    std::map<FSMStateID, std::shared_ptr<State>> state_map_;
    std::shared_ptr<State> current_state_;
};

} // namespace atrop::fsm
