#include "daemon/control_plane/fsm/fsm_engine.hpp"
#include "daemon/control_plane/fsm/states/init_state.hpp"
#include "daemon/control_plane/fsm/states/discovery_state.hpp"
#include "daemon/control_plane/fsm/states/decide_state.hpp"
#include "daemon/control_plane/fsm/states/exit_state.hpp"
#include "daemon/common/logger.hpp"
#include <gtest/gtest.h>
#include <memory>
#include <string>

// Stub logger for FSM tests
std::shared_ptr<spdlog::logger> get_test_logger() {
    atrop::Logger::init("FSMTest", "debug", "");
    return atrop::Logger::get();
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

    fsm.start("INIT");
    EXPECT_EQ(fsm.current_state_name(), "INIT");

    ASSERT_TRUE(fsm.transition_to("DISCOVERY"));
    EXPECT_EQ(fsm.current_state_name(), "DISCOVERY");

    ASSERT_TRUE(fsm.transition_to("DECIDE"));
    EXPECT_EQ(fsm.current_state_name(), "DECIDE");

    ASSERT_TRUE(fsm.transition_to("EXIT"));
    EXPECT_EQ(fsm.current_state_name(), "EXIT");
}

TEST(FSMTest, EventDrivenTransitions) {
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

    fsm.add_transition("INIT", FSMEvent::RegistrationComplete, "DISCOVERY");
    fsm.add_transition("DISCOVERY", FSMEvent::TopologyStable, "DECIDE");
    fsm.add_transition("DECIDE", FSMEvent::TrustRevoked, "EXIT");

    fsm.start("INIT");
    EXPECT_EQ(fsm.current_state_name(), "INIT");

    // Valid event-driven transition
    ASSERT_TRUE(fsm.handle_event(FSMEvent::RegistrationComplete));
    EXPECT_EQ(fsm.current_state_name(), "DISCOVERY");

    // Valid event-driven transition
    ASSERT_TRUE(fsm.handle_event(FSMEvent::TopologyStable));
    EXPECT_EQ(fsm.current_state_name(), "DECIDE");

    // Valid event-driven transition to EXIT
    ASSERT_TRUE(fsm.handle_event(FSMEvent::TrustRevoked));
    EXPECT_EQ(fsm.current_state_name(), "EXIT");
}

TEST(FSMTest, InvalidEventLoggingAndBlock) {
    auto logger = get_test_logger();
    FSMEngine fsm(logger);

    auto init = std::make_shared<InitState>(logger);
    auto discovery = std::make_shared<DiscoveryState>(logger);

    fsm.register_state("INIT", init);
    fsm.register_state("DISCOVERY", discovery);

    fsm.add_transition("INIT", FSMEvent::RegistrationComplete, "DISCOVERY");

    fsm.start("INIT");
    EXPECT_EQ(fsm.current_state_name(), "INIT");

    // Invalid event for INIT (not in transition table)
    EXPECT_FALSE(fsm.handle_event(FSMEvent::TopologyStable));
    EXPECT_EQ(fsm.current_state_name(), "INIT");

    // Valid event
    ASSERT_TRUE(fsm.handle_event(FSMEvent::RegistrationComplete));
    EXPECT_EQ(fsm.current_state_name(), "DISCOVERY");

    // Invalid event for DISCOVERY (not in transition table)
    EXPECT_FALSE(fsm.handle_event(FSMEvent::TrustRevoked));
    EXPECT_EQ(fsm.current_state_name(), "DISCOVERY");
}

TEST(FSMTest, EdgeCases) {
    auto logger = get_test_logger();
    FSMEngine fsm(logger);

    auto init = std::make_shared<InitState>(logger);
    fsm.register_state("INIT", init);

    // Start with missing state
    FSMEngine fsm2(logger);
    fsm2.start("MISSING");
    EXPECT_NE(fsm2.current_state_name(), "MISSING");

    // Double transition to same state
    fsm.start("INIT");
    EXPECT_TRUE(fsm.transition_to("INIT"));
    EXPECT_EQ(fsm.current_state_name(), "INIT");

    // Unknown event (not in enum)
    // This is not possible in C++, but we can check the default case in event_to_string
    std::string unknown = fsm.event_to_string(static_cast<FSMEvent>(999));
    EXPECT_EQ(unknown, "Unknown");
}
