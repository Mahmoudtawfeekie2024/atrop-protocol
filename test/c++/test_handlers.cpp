#include <gtest/gtest.h>
#include <string>

// Use local includes since CMake adds daemon/handlers to the include path
#include "discovery_handler.hpp"
#include "decision_handler.hpp"
#include "observation_handler.hpp"
#include "correction_handler.hpp"
#include "security_handler.hpp"
#include "exit_handler.hpp"

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
