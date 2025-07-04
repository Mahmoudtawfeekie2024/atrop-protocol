#include "discovery_handler.hpp"
#include <iostream>
#include <string>

std::string handleDiscoveryPacket(const std::string& raw_packet) {
    std::cout << "[STUB] Received Discovery packet (stub handler)" << std::endl;
    // TODO: Parse raw_packet for Discovery fields (NIV, node_id, etc.)
    // FIXME: Implement full parsing and dispatch in Phase 2 (see T2-03)
    return "[STUB] Received Discovery packet (stub handler)";
}
