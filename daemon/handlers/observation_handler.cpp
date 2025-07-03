#include "../common/logger.hpp"
#include <vector>
#include <cstdint>

namespace atrop {
namespace control_plane {

void handleObservationPacket(const std::vector<uint8_t>& packet) {
    LOG_INFO("Received OBSERVATION packet");

    // TODO: Extract Feedback Injection Field (FIF)
    // TODO: Extract Node Identity Vector (NIV)
    // FIXME: Connect to FSM for FEEDBACK → CORRECT transition
}

}  // namespace control_plane
}  // namespace atrop
