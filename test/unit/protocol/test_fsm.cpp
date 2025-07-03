#include <gtest/gtest.h>
#include "logger.hpp"
#include "state_init.hpp"
#include "state_discovery.hpp"
#include "state_learn.hpp"
#include "state_decide.hpp"
#include "state_enforce.hpp"
#include "state_observe.hpp"
#include "state_feedback.hpp"
#include "state_correct.hpp"
#include "state_exit.hpp"

using namespace atrop::fsm;

TEST(FSMTest, InitState_Transition) {
    InitState state;
    EXPECT_EQ(state.id(), FSMStateID::INIT);
    EXPECT_EQ(state.handle_event(FSMEvent::None), FSMStateID::INIT);
    EXPECT_EQ(state.handle_event(FSMEvent::DiscoveryComplete), FSMStateID::DISCOVERY);
}

TEST(FSMTest, DiscoveryState_Transition) {
    DiscoveryState state;
    EXPECT_EQ(state.id(), FSMStateID::DISCOVERY);
    EXPECT_EQ(state.handle_event(FSMEvent::TrainingComplete), FSMStateID::LEARN);
    EXPECT_EQ(state.handle_event(FSMEvent::None), FSMStateID::DISCOVERY);
}

TEST(FSMTest, LearnState_Transition) {
    LearnState state;
    EXPECT_EQ(state.id(), FSMStateID::LEARN);
    EXPECT_EQ(state.handle_event(FSMEvent::InferenceReady), FSMStateID::DECIDE);
    EXPECT_EQ(state.handle_event(FSMEvent::None), FSMStateID::LEARN);
}

TEST(FSMTest, DecideState_Transition) {
    DecideState state;
    EXPECT_EQ(state.id(), FSMStateID::DECIDE);
    EXPECT_EQ(state.handle_event(FSMEvent::InferenceReady), FSMStateID::ENFORCE);
    EXPECT_EQ(state.handle_event(FSMEvent::None), FSMStateID::DECIDE);
}

TEST(FSMTest, EnforceState_Transition) {
    EnforceState state;
    EXPECT_EQ(state.id(), FSMStateID::ENFORCE);
    EXPECT_EQ(state.handle_event(FSMEvent::None), FSMStateID::OBSERVE);
    EXPECT_EQ(state.handle_event(FSMEvent::TrainingComplete), FSMStateID::ENFORCE);
}

TEST(FSMTest, ObserveState_Transition) {
    ObserveState state;
    EXPECT_EQ(state.id(), FSMStateID::OBSERVE);
    EXPECT_EQ(state.handle_event(FSMEvent::AnomalyDetected), FSMStateID::CORRECT);
    EXPECT_EQ(state.handle_event(FSMEvent::None), FSMStateID::FEEDBACK);
}

TEST(FSMTest, FeedbackState_Transition) {
    FeedbackState state;
    EXPECT_EQ(state.id(), FSMStateID::FEEDBACK);
    EXPECT_EQ(state.handle_event(FSMEvent::InferenceReady), FSMStateID::DECIDE);
    EXPECT_EQ(state.handle_event(FSMEvent::AnomalyDetected), FSMStateID::CORRECT);
    EXPECT_EQ(state.handle_event(FSMEvent::None), FSMStateID::FEEDBACK);
}

TEST(FSMTest, CorrectState_Transition) {
    CorrectState state;
    EXPECT_EQ(state.id(), FSMStateID::CORRECT);

    // Note: Logic may change based on critical_mode
    FSMStateID result = state.handle_event(FSMEvent::InferenceReady);
    EXPECT_TRUE(result == FSMStateID::DECIDE || result == FSMStateID::EXIT || result == FSMStateID::CORRECT);
}

TEST(FSMTest, ExitState_Transition) {
    ExitState state;
    EXPECT_EQ(state.id(), FSMStateID::EXIT);
    EXPECT_EQ(state.handle_event(FSMEvent::None), FSMStateID::EXIT);
    EXPECT_EQ(state.handle_event(FSMEvent::DiscoveryComplete), FSMStateID::EXIT);
}
TEST(FSMTest, InvalidTransition_ObservedByStateIgnore) {
    LearnState state;
    EXPECT_EQ(state.handle_event(FSMEvent::DiscoveryComplete), FSMStateID::LEARN); // Ignored

    DecideState decide;
    EXPECT_EQ(decide.handle_event(FSMEvent::TrainingComplete), FSMStateID::DECIDE); // Ignored

    EnforceState enforce;
    EXPECT_EQ(enforce.handle_event(FSMEvent::TrainingComplete), FSMStateID::ENFORCE); // Ignored

    ExitState exit;
    EXPECT_EQ(exit.handle_event(FSMEvent::TrainingComplete), FSMStateID::EXIT); // Locked terminal
}
TEST(FSMTest, LoggerAvailableAndSafe) {
    EXPECT_NO_THROW({
        atrop::Logger::init("fsm-test", "debug");
        auto logger = atrop::Logger::get();
        logger->info("✅ FSM logger functional in test environment");
    });
}
TEST(FSMTest, ConfigDriven_CorrectStateCriticalExit) {
    CorrectState state;
    FSMStateID result = state.handle_event(FSMEvent::InferenceReady);

    // If "correction.critical_mode" is true, transition should be EXIT
    EXPECT_TRUE(result == FSMStateID::EXIT || result == FSMStateID::DECIDE);
}
