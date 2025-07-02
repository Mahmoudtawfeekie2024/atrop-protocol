#include <iostream>
#include <config_loader.hpp>  // Clean, thanks to target_include_directories

int main() {
    std::cout << "ATROP Control Plane Daemon starting..." << std::endl;

    try {
        auto config = ConfigLoader::load("config.yaml");
        std::cout << "[CONFIG] Successfully loaded values:\n";
        for (const auto& [key, val] : config) {
            std::visit([&key](auto&& arg) {
                std::cout << "  " << key << ": " << arg << "\n";
            }, val);
        }
    } catch (const std::exception& e) {
        std::cerr << "[CONFIG] Error loading config: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
