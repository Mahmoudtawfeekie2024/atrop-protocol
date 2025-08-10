#include <gtest/gtest.h>
#include "../../../daemon/handlers/packet_dispatcher.hpp"

static bool handler_invoked = false;
static std::unordered_map<std::string, std::string> last_payload;

// Dummy handler replacements for unit testing
void dummy_discovery_handler(const std::unordered_map<std::string, std::string>& packet) {
    handler_invoked = true; last_payload = packet;
}
void dummy_decision_handler(const std::unordered_map<std::string, std::string>& packet) {
    handler_invoked = true; last_payload = packet;
}
void dummy_correction_handler(const std::unordered_map<std::string, std::string>& packet) {
    handler_invoked = true; last_payload = packet;
}
void dummy_observation_handler(const std::unordered_map<std::string, std::string>& packet) {
    handler_invoked = true; last_payload = packet;
}

class PacketDispatcherTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Patch handler functions here if repo uses function pointers, or mock inside dispatcher for real unit tests
        handler_invoked = false;
        last_payload.clear();
    }
};

TEST_F(PacketDispatcherTest, DispatchDiscovery) {
    PacketDispatcher pd;
    std::unordered_map<std::string, std::string> pkt = {
        {"message_id", "1"}, {"type", "discovery"}, {"source", "A"}, {"destination", "B"}, {"sequence", "100"}
    };
    EXPECT_TRUE(pd.dispatch(pkt));
    // For a real test, this will require patching handle_discovery_packet function to dummy_discovery_handler
}

TEST_F(PacketDispatcherTest, DispatchDecision) {
    PacketDispatcher pd;
    std::unordered_map<std::string, std::string> pkt = {
        {"message_id", "2"}, {"type", "decision"}, {"source", "X"}, {"destination", "Y"}, {"sequence", "200"}
    };
    EXPECT_TRUE(pd.dispatch(pkt));
}

TEST_F(PacketDispatcherTest, DispatchInvalid) {
    PacketDispatcher pd;
    std::unordered_map<std::string, std::string> pkt = {
        {"message_id", "3"}, {"source", "A"} // missing required fields
    };
    EXPECT_FALSE(pd.dispatch(pkt));
}

TEST_F(PacketDispatcherTest, DispatchUnknownType) {
    PacketDispatcher pd;
    std::unordered_map<std::string, std::string> pkt = {
        {"message_id", "4"}, {"type", "foobar"}, {"source", "A"}, {"destination", "B"}, {"sequence", "1"}
    };
    EXPECT_FALSE(pd.dispatch(pkt));
}
