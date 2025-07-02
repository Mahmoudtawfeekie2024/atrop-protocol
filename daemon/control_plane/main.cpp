// daemon/control_plane/main.cpp

#include <iostream>
#include <string>
#include <config_loader.hpp>  // Clean, thanks to target_include_directories

int main() {
    std::cout << "ATROP Control Plane Daemon starting..." << std::endl;

    try {
        const std::string config_path = "config.yaml";
        auto config = ConfigLoader::load(config_path);

        std::cout << "[CONFIG] Selected Values:\n";
        std::cout << "  Port: " << std::get<int>(config["module.port"]) << "\n";
        std::cout << "  Timeout: " << std::get<int>(config["module.timeout"]) << "\n";
        std::cout << "  Log Level: " << std::get<std::string>(config["module.log_level"]) << "\n";
        std::cout << "  Environment Mode: " << std::get<std::string>(config["environment.mode"]) << "\n";

        std::cout << "[CONFIG] Full Configuration:\n";
        for (const auto& [key, val] : config) {
            std::visit([&key](auto&& arg) {
                std::cout << "  " << key << ": " << arg << "\n";
            }, val);
        }
    } catch (const std::exception& e) {
        std::cerr << "[CONFIG] Error loading config: " << e.what() << std::endl;
        return 1;
    }

    // TODO: Start gRPC server, FSM, etc.
    return 0;
}
