#include <gtest/gtest.h>
#include <string>

// Include the actual handler headers
#include "daemon/handlers/discovery_handler.hpp"
#include "daemon/handlers/decision_handler.hpp"
#include "daemon/handlers/observation_handler.hpp"
#include "daemon/handlers/correction_handler.hpp"
#include "daemon/handlers/security_handler.hpp"
#include "daemon/handlers/exit_handler.hpp"

TEST(HandlerTest, DiscoveryPacket) {
    std::string input = "test_discovery";
    auto result = handleDiscoveryPacket(input);
    EXPECT_FALSE(result.empty());
}

TEST(HandlerTest, DecisionPacket) {
    std::string input = "test_decision";
    auto result = handleDecisionPacket(input);
    EXPECT_FALSE(result.empty());
}

TEST(HandlerTest, ObservationPacket) {
    std::string input = "test_observation";
    auto result = handleObservationPacket(input);
    EXPECT_FALSE(result.empty());
}

TEST(HandlerTest, CorrectionPacket) {
    std::string input = "test_correction";
    auto result = handleCorrectionPacket(input);
    EXPECT_FALSE(result.empty());
}

TEST(HandlerTest, SecurityPacket) {
    std::string input = "test_security";
    auto result = handleSecurityPacket(input);
    EXPECT_FALSE(result.empty());
}

TEST(HandlerTest, ExitPacket) {
    std::string input = "test_exit";
    auto result = handleExitPacket(input);
    EXPECT_FALSE(result.empty());
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
