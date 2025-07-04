#include "fsm_engine.hpp"
#include <gtest/gtest.h>
#include <memory>
#include <string>
#include "daemon/control_plane/fsm/fsm_engine.hpp"
#include "daemon/control_plane/fsm/states/init_state.hpp"
#include "daemon/control_plane/fsm/states/discovery_state.hpp"
#include "daemon/control_plane/fsm/states/decide_state.hpp"
#include "daemon/control_plane/fsm/states/exit_state.hpp"
#include "daemon/common/logger.hpp"

// Stub logger for tests
std::shared_ptr<spdlog::logger> get_test_logger() {
    // Logger::init returns void, so just call it for side effects
    atrop::Logger::init("FSMTest", "debug", "");
    return atrop::Logger::get();
}

TEST(FSMTest, StateEntryExit) {
    auto logger = get_test_logger();
    FSMEngine fsm(logger);

    auto init = std::make_shared<InitState>(logger);
    auto discovery = std::make_shared<DiscoveryState>(logger);
    auto decide = std::make_shared<DecideState>(logger);
    auto exit_state = std::make_shared<ExitState>(logger);

    fsm.register_state("INIT", init);
    fsm.register_state("DISCOVERY", discovery);
    fsm.register_state("DECIDE", decide);
    fsm.register_state("EXIT", exit_state);

    // Start FSM at INIT
    fsm.start("INIT");
    EXPECT_EQ(fsm.current_state_name(), "INIT");

    // Transition to DISCOVERY
    ASSERT_TRUE(fsm.transition_to("DISCOVERY"));
    EXPECT_EQ(fsm.current_state_name(), "DISCOVERY");

    // Transition to DECIDE
    ASSERT_TRUE(fsm.transition_to("DECIDE"));
    EXPECT_EQ(fsm.current_state_name(), "DECIDE");

    // Transition to EXIT
    ASSERT_TRUE(fsm.transition_to("EXIT"));
    EXPECT_EQ(fsm.current_state_name(), "EXIT");
}

TEST(FSMTest, InvalidTransition) {
    auto logger = get_test_logger();
    FSMEngine fsm(logger);

    auto init = std::make_shared<InitState>(logger);
    fsm.register_state("INIT", init);

    fsm.start("INIT");
    EXPECT_FALSE(fsm.transition_to("NON_EXISTENT"));
    EXPECT_EQ(fsm.current_state_name(), "INIT");
}

TEST(FSMTest, RepeatedEntryExit) {
    auto logger = get_test_logger();
    FSMEngine fsm(logger);

    auto init = std::make_shared<InitState>(logger);
    auto exit_state = std::make_shared<ExitState>(logger);

    fsm.register_state("INIT", init);
    fsm.register_state("EXIT", exit_state);

    fsm.start("INIT");
    ASSERT_TRUE(fsm.transition_to("EXIT"));
    // Transition back to INIT
    ASSERT_TRUE(fsm.transition_to("INIT"));
    EXPECT_EQ(fsm.current_state_name(), "INIT");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
