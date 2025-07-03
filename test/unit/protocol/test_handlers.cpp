#include <gtest/gtest.h>
#include "../../../daemon/control_plane/handlers/discovery_handler.cpp"
#include "../../../daemon/control_plane/handlers/decision_handler.cpp"
#include "../../../daemon/control_plane/handlers/observation_handler.cpp"

TEST(HandlerStubsTest, DiscoveryHandlerRuns) {
    std::vector<uint8_t> dummy_packet = {0x01, 0xAA, 0xBB};
    EXPECT_NO_THROW(atrop::control_plane::handleDiscoveryPacket(dummy_packet));
}

TEST(HandlerStubsTest, DecisionHandlerRuns) {
    std::vector<uint8_t> dummy_packet = {0x02, 0xCC, 0xDD};
    EXPECT_NO_THROW(atrop::control_plane::handleDecisionPacket(dummy_packet));
}

TEST(HandlerStubsTest, ObservationHandlerRuns) {
    std::vector<uint8_t> dummy_packet = {0x03, 0xEE, 0xFF};
    EXPECT_NO_THROW(atrop::control_plane::handleObservationPacket(dummy_packet));
}
