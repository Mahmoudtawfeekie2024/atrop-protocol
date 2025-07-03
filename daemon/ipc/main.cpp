// daemon/ipc/main.cpp

#include <iostream>
#include <string>
#include "sdk/c++/config_loader.hpp"
// ... rest of your includes and code

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
    // Simulated packet type (e.g., from IPC buffer or test)
    uint8_t packet_type = 0x01;  // Mock DISCOVERY for now
    std::vector<uint8_t> packet = { /* placeholder bytes */ };

    // Include handler stubs
    #include "../control_plane/handlers/discovery_handler.cpp"
    #include "../control_plane/handlers/decision_handler.cpp"
    #include "../control_plane/handlers/observation_handler.cpp"

    switch (packet_type) {
        case 0x01:  // DISCOVERY
            atrop::control_plane::handleDiscoveryPacket(packet);
            break;
        case 0x02:  // DECISION
            atrop::control_plane::handleDecisionPacket(packet);
            break;
        case 0x03:  // OBSERVATION
            atrop::control_plane::handleObservationPacket(packet);
            break;
        default:
            std::cout << "[DISPATCH] Unknown packet type: " << static_cast<int>(packet_type) << std::endl;
    }

    return 0;
}
