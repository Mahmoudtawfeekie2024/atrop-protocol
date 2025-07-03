#include "discovery_handler.hpp"
#include "logger.hpp"
#include <iostream>
#include <vector>
#include <cstdint>

namespace atrop {
namespace control_plane {

void handleDiscoveryPacket(const std::vector<uint8_t>& packet) {
    LOG_INFO("🧭 Received Discovery Packet | Size: {} bytes", packet.size());

    // TODO: Parse Node Identity Vector (NIV)
    // TODO: Parse Path Intelligence Vector (PIV)
    // TODO: Parse Intent Descriptor (IDR)

    // FIXME: Integrate with FSM dispatch
}

}  // namespace control_plane
}  // namespace atrop
