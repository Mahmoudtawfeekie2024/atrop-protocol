// daemon/ipc/discovery_handler.cpp

#include "discovery_handler.hpp"
#include <iostream>

/**
 * T1-09 Discovery Packet Handler (stub)
 * Handles Discovery packets (initial node intro, topology discovery)
 * Expected fields: NIV, node_id, zone_info, etc.
 * TODO: Implement full parsing and dispatch in Phase 2 (see T2-03)
 */
void handleDiscoveryPacket(const std::string& raw_packet) {
    std::cout << "[STUB] Received Discovery packet (stub handler)" << std::endl;
    // TODO: Parse raw_packet for Discovery fields (NIV, node_id, etc.)
    // FIXME: Implement full parsing and dispatch in Phase 2 (see T2-03)
}
