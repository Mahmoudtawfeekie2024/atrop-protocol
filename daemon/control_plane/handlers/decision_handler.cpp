#include "atrop_packet_handlers.hpp"
#include "logger.hpp"
#include <iostream>
#include <vector>
#include <cstdint>

namespace atrop {
namespace control_plane {

void handleDecisionPacket(const std::vector<uint8_t>& packet) {
    LOG_INFO("🧠 Received Decision Packet | Size: {} bytes", packet.size());

    // TODO: Parse Node Identity Vector (NIV)
    // TODO: Parse Path Intelligence Vector (PIV)
    // TODO: Parse Intent Descriptor (IDR)

    // FIXME: Integrate with FSM dispatch
}

}  // namespace control_plane
}  // namespace atrop
