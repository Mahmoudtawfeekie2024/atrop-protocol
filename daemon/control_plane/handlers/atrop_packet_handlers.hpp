// daemon/control_plane/handlers/atrop_packet_handlers.hpp

#pragma once

#include <vector>
#include <cstdint>

namespace atrop {
namespace control_plane {

enum AtropPacketType : uint8_t {
    ATROP_DISCOVERY   = 0x01,
    ATROP_DECISION    = 0x02,
    ATROP_OBSERVATION = 0x03
};

void handleDiscoveryPacket(const std::vector<uint8_t>& packet);
void handleDecisionPacket(const std::vector<uint8_t>& packet);
void handleObservationPacket(const std::vector<uint8_t>& packet);

}  // namespace control_plane
}  // namespace atrop
