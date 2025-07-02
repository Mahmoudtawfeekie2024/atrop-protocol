// daemon/control_plane/main.cpp

#include <iostream>
#include <string>
#include <config_loader.hpp>     // Clean, thanks to target_include_directories
#include <logger.hpp>            // Add this header

int main() {
    std::cout << "ATROP Control Plane Daemon starting..." << std::endl;

    try {
        const std::string config_path = "config.yaml";
        auto config = ConfigLoader::load(config_path);

        // Load logging settings
        std::string log_level = std::get<std::string>(config["module.log_level"]);
        std::string log_file = "atrop-control.log";  // Optional: get from config too

        atrop::Logger::init("ATROP.Control", log_level, log_file);
        auto log = atrop::Logger::get();

        log->info("Logger initialized with level '{}'", log_level);
        log->info("Configuration loaded from '{}'", config_path);

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
            log->error("Failed to load config: {}", e.what());
        }
        return 1;
    }

    // TODO: Start gRPC server, FSM, etc.
    return 0;
}
