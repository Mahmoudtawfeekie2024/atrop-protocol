// daemon/control_plane/fsm/fsm_transitions.hpp
#pragma once

#include "state_base.hpp"
#include <unordered_map>
#include <vector>
#include <algorithm>

namespace atrop::fsm {

inline const std::unordered_map<FSMStateID, std::vector<FSMStateID>> VALID_TRANSITIONS = {
    { FSMStateID::INIT,      { FSMStateID::DISCOVERY } },
    { FSMStateID::DISCOVERY, { FSMStateID::LEARN } },
    { FSMStateID::LEARN,     { FSMStateID::DECIDE } },
    { FSMStateID::DECIDE,    { FSMStateID::ENFORCE } },
    { FSMStateID::ENFORCE,   { FSMStateID::OBSERVE } },
    { FSMStateID::OBSERVE,   { FSMStateID::FEEDBACK, FSMStateID::CORRECT } },
    { FSMStateID::FEEDBACK,  { FSMStateID::DECIDE, FSMStateID::CORRECT } },
    { FSMStateID::CORRECT,   { FSMStateID::DECIDE, FSMStateID::EXIT } },
    { FSMStateID::EXIT,      {} }
};

inline bool is_valid_transition(FSMStateID from, FSMStateID to) {
    const auto& allowed = VALID_TRANSITIONS.at(from);
    return std::find(allowed.begin(), allowed.end(), to) != allowed.end();
}

} // namespace atrop::fsm
