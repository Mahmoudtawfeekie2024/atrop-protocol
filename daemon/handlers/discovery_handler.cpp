#include "../common/logger.hpp"
#include <vector>
#include <cstdint>

namespace atrop {
namespace control_plane {

void handleDiscoveryPacket(const std::vector<uint8_t>& packet) {
    LOG_INFO("Received DISCOVERY packet from mock_node_id=NODE-01");

    // TODO: Extract Node Identity Vector (NIV)
    // TODO: Extract Intent Descriptor (IDR)
    // FIXME: Connect to FSM for DISCOVERY → LEARN transition
}

}  // namespace control_plane
}  // namespace atrop
