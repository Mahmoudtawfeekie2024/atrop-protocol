#include <iostream>
#include <string>
#include <config_loader.hpp>
#include "../handlers/discovery_handler.hpp"
#include "../handlers/decision_handler.hpp"
#include "../handlers/observation_handler.hpp"
#include "../handlers/correction_handler.hpp"
#include "../handlers/security_handler.hpp"
#include "../handlers/exit_handler.hpp"

int main() {
    std::cout << "ATROP IPC Daemon starting..." << std::endl;

    try {
        auto config = ConfigLoader::load("config.yaml");

        std::cout << "[CONFIG] Port: " << std::get<int>(config["module.port"]) << "\n";
        std::cout << "[CONFIG] Timeout: " << std::get<int>(config["module.timeout"]) << "\n";
        std::cout << "[CONFIG] Environment Mode: " << std::get<std::string>(config["environment.mode"]) << "\n";
        std::cout << "[CONFIG] Log Directory: " << std::get<std::string>(config["paths.log_dir"]) << "\n";

        std::cout << "[CONFIG] IPC Config Loaded Successfully.\n";
    } catch (const std::exception& e) {
        std::cerr << "[CONFIG] Error loading config: " << e.what() << std::endl;
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

    // TODO: Start IPC interface, queue handlers, etc.
    return 0;
}
