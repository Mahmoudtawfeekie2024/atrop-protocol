// daemon/ipc/main.cpp

#include <iostream>
#include <string>
#include <config_loader.hpp>  // Clean, thanks to target_include_directories

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

    // TODO: Start IPC interface, queue handlers, etc.
    return 0;
}
