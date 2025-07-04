#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <config_loader.hpp>
#include "logger.hpp"
#include "../handlers/discovery_handler.hpp"
#include "../handlers/decision_handler.hpp"
#include "../handlers/observation_handler.hpp"
#include "../handlers/correction_handler.hpp"
#include "../handlers/security_handler.hpp"
#include "../handlers/exit_handler.hpp"
#include "../fsm/fsm_engine.hpp"
#include "../fsm/states/init_state.hpp"
#include "../fsm/states/discovery_state.hpp"
#include "../fsm/states/learn_state.hpp"
#include "../fsm/states/decide_state.hpp"
#include "../fsm/states/enforce_state.hpp"
#include "../fsm/states/observe_state.hpp"
#include "../fsm/states/feedback_state.hpp"
#include "../fsm/states/correct_state.hpp"
#include "../fsm/states/exit_state.hpp"

int main() {
    std::cout << "ATROP Control Plane Daemon starting..." << std::endl;

    try {
        const std::string config_path = "config.yaml";
        auto config = ConfigLoader::load(config_path);

        // --- Logging config ---
        std::string log_level = "info";
        std::string log_format = "text";
        std::string log_file = "atrop-control.log";

        if (config.count("module.log_level"))
            log_level = std::get<std::string>(config["module.log_level"]);

        if (config.count("module.log_format"))
            log_format = std::get<std::string>(config["module.log_format"]);

        if (config.count("module.log_file"))
            log_file = std::get<std::string>(config["module.log_file"]);

        // --- Initialize logger based on config ---
        atrop::Logger::init("ATROP.Control", log_level, log_file);
        if (log_format == "json") {
            atrop::Logger::get()->set_pattern(R"({"ts":"%Y-%m-%d %H:%M:%S","level":"%l","name":"%n","msg":"%v"})");
        }

        auto log = atrop::Logger::get();
        log->info("Logger initialized from '{}'", config_path);
        log->info("Log Level: '{}', Format: '{}', File: '{}'", log_level, log_format, log_file);

        // --- Print config summary ---
        log->info("Selected Config:");
        log->info("  Port: {}", std::get<int>(config["module.port"]));
        log->info("  Timeout: {}", std::get<int>(config["module.timeout"]));
        log->info("  Environment: {}", std::get<std::string>(config["environment.mode"]));

        log->debug("Full Configuration:");
        for (const auto& [key, val] : config) {
            std::visit([&](auto&& arg) {
                log->debug("  {}: {}", key, arg);
            }, val);
        }

        // --- FSM Engine and State Registration ---
        auto fsm_logger = atrop::Logger::get();
        FSMEngine fsm(fsm_logger);

        // Instantiate all states with logger
        fsm.register_state("INIT", std::make_shared<InitState>(fsm_logger));
        fsm.register_state("DISCOVERY", std::make_shared<DiscoveryState>(fsm_logger));
        fsm.register_state("LEARN", std::make_shared<LearnState>(fsm_logger));
        fsm.register_state("DECIDE", std::make_shared<DecideState>(fsm_logger));
        fsm.register_state("ENFORCE", std::make_shared<EnforceState>(fsm_logger));
        fsm.register_state("OBSERVE", std::make_shared<ObserveState>(fsm_logger));
        fsm.register_state("FEEDBACK", std::make_shared<FeedbackState>(fsm_logger));
        fsm.register_state("CORRECT", std::make_shared<CorrectState>(fsm_logger));
        fsm.register_state("EXIT", std::make_shared<ExitState>(fsm_logger));

        // --- FSM Transition Table Setup ---
        fsm.add_transition("INIT", FSMEvent::RegistrationComplete, "DISCOVERY");
        fsm.add_transition("DISCOVERY", FSMEvent::NeighborsMapped, "LEARN");
        fsm.add_transition("LEARN", FSMEvent::TopologyStable, "DECIDE");
        fsm.add_transition("DECIDE", FSMEvent::PolicyApproved, "ENFORCE");
        fsm.add_transition("ENFORCE", FSMEvent::ForwardingActive, "OBSERVE");
        fsm.add_transition("OBSERVE", FSMEvent::TelemetryThreshold, "FEEDBACK");
        fsm.add_transition("FEEDBACK", FSMEvent::ModelUpdated, "DECIDE");
        fsm.add_transition("DECIDE", FSMEvent::AnomalyViolation, "CORRECT");
        fsm.add_transition("ENFORCE", FSMEvent::AnomalyViolation, "CORRECT");
        fsm.add_transition("CORRECT", FSMEvent::FallbackRecovery, "OBSERVE");
        fsm.add_transition("CORRECT", FSMEvent::CorrectionApplied, "LEARN");
        fsm.add_transition("CORRECT", FSMEvent::TrustRevoked, "EXIT");
        fsm.add_transition("FEEDBACK", FSMEvent::NodeShutdown, "EXIT");

        // Emergency/manual transitions (ANY state)
        std::vector<std::string> all_states = {
            "INIT", "DISCOVERY", "LEARN", "DECIDE", "ENFORCE", "OBSERVE", "FEEDBACK", "CORRECT", "EXIT"
        };
        for (const auto& state : all_states) {
            fsm.add_transition(state, FSMEvent::ManualOverride, "CORRECT");
            fsm.add_transition(state, FSMEvent::ManualReset, "INIT");
        }

        // --- Start FSM at INIT state ---
        fsm.start("INIT");

        // --- Demonstrate event-driven transitions ---
        fsm.handle_event(FSMEvent::RegistrationComplete); // INIT -> DISCOVERY
        fsm.handle_event(FSMEvent::NeighborsMapped);      // DISCOVERY -> LEARN
        fsm.handle_event(FSMEvent::TopologyStable);       // LEARN -> DECIDE
        fsm.handle_event(FSMEvent::PolicyApproved);       // DECIDE -> ENFORCE
        fsm.handle_event(FSMEvent::ForwardingActive);     // ENFORCE -> OBSERVE
        fsm.handle_event(FSMEvent::TelemetryThreshold);   // OBSERVE -> FEEDBACK
        fsm.handle_event(FSMEvent::ModelUpdated);         // FEEDBACK -> DECIDE
        fsm.handle_event(FSMEvent::AnomalyViolation);     // DECIDE -> CORRECT
        fsm.handle_event(FSMEvent::FallbackRecovery);     // CORRECT -> OBSERVE
        fsm.handle_event(FSMEvent::ManualOverride);       // OBSERVE -> CORRECT (emergency)
        fsm.handle_event(FSMEvent::TrustRevoked);         // CORRECT -> EXIT

    } catch (const std::exception& e) {
        std::cerr << "[CONFIG] Error loading config: " << e.what() << std::endl;
        if (auto log = atrop::Logger::get()) {
            log->error("Startup failed due to config error: {}", e.what());
        }
        return 1;
    }

    // Simulate receiving a Discovery packet (stub)
    handleDiscoveryPacket("DISCOVERY_PACKET_PLACEHOLDER");

    // Simulate receiving a Decision packet (stub)
    handleDecisionPacket("DECISION_PACKET_PLACEHOLDER");

    // Simulate receiving an Observation packet (stub)
    handleObservationPacket("OBSERVATION_PACKET_PLACEHOLDER");

    // Simulate receiving a Correction packet (stub)
    handleCorrectionPacket("CORRECTION_PACKET_PLACEHOLDER");

    // Simulate receiving a Security packet (stub)
    handleSecurityPacket("SECURITY_PACKET_PLACEHOLDER");

    // Simulate receiving an Exit packet (stub)
    handleExitPacket("EXIT_PACKET_PLACEHOLDER");

    // TODO: Start gRPC server, FSM, etc.
    return 0;
}
