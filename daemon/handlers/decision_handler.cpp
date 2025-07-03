#include "../common/logger.hpp"
#include <vector>
#include <cstdint>

namespace atrop {
namespace control_plane {

void handleDecisionPacket(const std::vector<uint8_t>& packet) {
    LOG_INFO("Received DECISION packet");

    // TODO: Extract Path Intelligence Vector (PIV)
    // TODO: Extract Intent Descriptor (IDR)
    // FIXME: Connect to FSM for DECIDE → ENFORCE transition
}

}  // namespace control_plane
}  // namespace atrop
