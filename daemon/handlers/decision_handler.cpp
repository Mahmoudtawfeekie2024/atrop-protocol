#include "decision_handler.hpp"
#include <iostream>
#include <string>

std::string handleDecisionPacket(const std::string& raw_packet) {
    std::cout << "[STUB] Received Decision packet (stub handler)" << std::endl;
    // TODO: Parse raw_packet for Decision fields (policy_id, route_vector, intent, etc.)
    // FIXME: Implement full parsing and dispatch in Phase 2 (see T2-04)
    return "[STUB] Received Decision packet (stub handler)";
}
