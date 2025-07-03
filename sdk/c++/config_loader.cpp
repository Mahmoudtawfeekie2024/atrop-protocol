// sdk/c++/config_loader.cpp
//
// Implementation of ConfigLoader for JSON/YAML configuration files.
// Loads into a flat map<string,ConfigValue>, applies defaults and
// validates required fields.
//

#include <config_loader.hpp>

#include <nlohmann/json.hpp>
#include <yaml-cpp/yaml.h>

#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <cctype>
#include <vector>

namespace sdk {

// alias for convenience
using json = nlohmann::json;

/**
 * @brief Apply default values for optional configuration keys.
 */
static void apply_defaults(std::map<std::string, ConfigValue>& config) {
    auto get_or = [&](const std::string& key, ConfigValue fallback) {
        auto it = config.find(key);
        return (it != config.end() ? it->second : fallback);
    };

    config["module.port"]        = get_or("module.port",        8080);
    config["module.timeout"]     = get_or("module.timeout",     10);
    config["module.log_level"]   = get_or("module.log_level",   std::string("INFO"));
    config["environment.mode"]   = get_or("environment.mode",   std::string("dev"));
    config["paths.model_dir"]    = get_or("paths.model_dir",    std::string("./models"));
    config["paths.data_dir"]     = get_or("paths.data_dir",     std::string("./data"));
    config["paths.log_dir"]      = get_or("paths.log_dir",      std::string("./logs"));
}

/**
 * @brief Ensure that all required keys are present.
 * @throws std::runtime_error if any are missing.
 */
static void validate_required_fields(const std::map<std::string, ConfigValue>& config) {
    const std::vector<std::string> required = {
        "module.port",
        "environment.mode",
        "paths.log_dir"
    };
    for (const auto& key : required) {
        if (config.find(key) == config.end()) {
            throw std::runtime_error("Missing required config field: " + key);
        }
    }
}

std::map<std::string, ConfigValue> ConfigLoader::load(const std::string& filepath) {
    std::map<std::string, ConfigValue> config;
    std::ifstream file(filepath);

    if (!file.is_open()) {
        throw std::runtime_error("Config file not found: " + filepath);
    }

    // Determine extension
    std::string ext;
    auto dot_pos = filepath.find_last_of('.');
    if (dot_pos != std::string::npos) {
        ext = filepath.substr(dot_pos);
        std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
    }

    try {
        if (ext == ".json") {
            // --- JSON Parsing ---
            json j;
            file >> j;

            if (!j.is_object()) {
                throw std::runtime_error("Config JSON must be an object at root");
            }

            for (auto it = j.begin(); it != j.end(); ++it) {
                const std::string key = it.key();
                const auto& value = it.value();

                if (value.is_string()) {
                    config[key] = value.get<std::string>();
                }
                else if (value.is_boolean()) {
                    config[key] = value.get<bool>();
                }
                else if (value.is_number_integer()) {
                    config[key] = value.get<int>();
                }
                else if (value.is_number_float()) {
                    config[key] = value.get<double>();
                }
                else {
                    throw std::runtime_error("Unsupported JSON type for key: " + key);
                }
            }
        }
        else if (ext == ".yaml" || ext == ".yml") {
            // --- YAML Parsing ---
            YAML::Node y = YAML::LoadFile(filepath);
            if (!y.IsMap()) {
                throw std::runtime_error("Config YAML must be a map at root");
            }

            for (auto it = y.begin(); it != y.end(); ++it) {
                const std::string key = it->first.as<std::string>();
                const YAML::Node val = it->second;

                if (val.IsScalar()) {
                    config[key] = val.as<std::string>();
                }
                // NOTE: nested maps/sequences intentionally ignored here
            }
        }
        else {
            throw std::runtime_error("Unsupported config file extension: " + ext);
        }
    }
    catch (const std::exception& e) {
        throw std::runtime_error("Failed to parse config (" + filepath + "): " + e.what());
    }

    // Apply defaults and validate
    apply_defaults(config);
    validate_required_fields(config);

    std::cout << "[CONFIG] Successfully loaded and validated: " << filepath << std::endl;
    return config;
}

} // namespace sdk
