// sdk/c++/config_loader.hpp

#pragma once

#include <string>
#include <map>
#include <variant>
#include <yaml-cpp/yaml.h>
#include <stdexcept>

namespace sdk {

using ConfigValue = std::variant<std::string, int, double, bool>;

class ConfigLoader {
public:
    /**
     * Load a configuration YAML file.
     * Returns the raw root YAML::Node object for structured access.
     *
     * Example:
     * auto config = sdk::ConfigLoader::load("config.yaml");
     * std::string id = config["node"]["id"].as<std::string>();
     */
    static YAML::Node load(const std::string& filepath) {
        try {
            return YAML::LoadFile(filepath);
        } catch (const std::exception& ex) {
            throw std::runtime_error("Failed to load config file: " + filepath + " — " + ex.what());
        }
    }
};

/**
 * Helper wrapper for shorthand loading.
 * Recommended usage in FSM or SDK modules:
 *     auto config = sdk::load_config("config.yaml");
 */
inline YAML::Node load_config(const std::string& filepath) {
    return ConfigLoader::load(filepath);
}

} // namespace sdk
