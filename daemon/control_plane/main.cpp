#include <iostream>
#include <map>
#include <string>
#include <variant>
#include "../../sdk/c++/config_loader.hpp"  // Adjust path if build system supports different include roots

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

    // TODO: Use config to drive AI policies, startup modes, etc.
    return 0;
}
