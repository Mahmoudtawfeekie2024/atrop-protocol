#pragma once
#include <vector>
#include <cstdint>
#include "atrop_packet_handlers.hpp"

namespace atrop {
namespace control_plane {

void handleObservationPacket(const std::vector<uint8_t>& packet);

}  // namespace control_plane
}  // namespace atrop
