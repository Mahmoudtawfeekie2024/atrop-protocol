#pragma once
#include <vector>
#include <cstdint>

namespace atrop {
namespace control_plane {

void handleObservationPacket(const std::vector<uint8_t>& packet);

}  // namespace control_plane
}  // namespace atrop
