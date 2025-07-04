// daemon/control_plane/main.cpp

#include <iostream>
#include <string>
#include <config_loader.hpp>
#include "logger.hpp"
#include "discovery_handler.hpp"
#include "decision_handler.hpp"
#include "observation_handler.hpp"
#include "correction_handler.hpp"
#include "security_handler.hpp"

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

    // TODO: Start gRPC server, FSM, etc.
    return 0;
}
