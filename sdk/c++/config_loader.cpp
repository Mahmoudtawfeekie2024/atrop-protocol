// sdk/c++/config_loader.cpp

#include "config_loader.hpp"
#include <nlohmann/json.hpp>
#include <yaml-cpp/yaml.h>
#include <fstream>
#include <stdexcept>
#include <algorithm>
#include <iostream>

using json = nlohmann::json;

static void apply_defaults(std::map<std::string, ConfigValue>& config) {
    auto get_or = [&](const std::string& key, ConfigValue fallback) {
        return config.count(key) ? config[key] : fallback;
    };

    config["module.port"] = get_or("module.port", 8080);
    config["module.timeout"] = get_or("module.timeout", 10);
    config["module.log_level"] = get_or("module.log_level", std::string("INFO"));
    config["environment.mode"] = get_or("environment.mode", std::string("dev"));
    config["paths.model_dir"] = get_or("paths.model_dir", std::string("./models"));
    config["paths.data_dir"] = get_or("paths.data_dir", std::string("./data"));
    config["paths.log_dir"] = get_or("paths.log_dir", std::string("./logs"));
}

static void validate_required_fields(const std::map<std::string, ConfigValue>& config) {
    const std::vector<std::string> required = {
        "module.port", "environment.mode", "paths.log_dir"
    };
    for (const auto& key : required) {
        if (!config.count(key)) {
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

    std::string ext;
    size_t dot_pos = filepath.find_last_of('.');
    if (dot_pos != std::string::npos)
        ext = filepath.substr(dot_pos);

    std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);

    try {
        if (ext == ".json") {
            json j;
            file >> j;
            for (auto& [key, value] : j.items()) {
                if (value.is_string()) config[key] = value.get<std::string>();
                else if (value.is_boolean()) config[key] = value.get<bool>();
                else if (value.is_number_integer()) config[key] = value.get<int>();
                else if (value.is_number_float()) config[key] = value.get<double>();
                else throw std::runtime_error("Unsupported JSON value for key: " + key);
            }
        }
        else if (ext == ".yaml" || ext == ".yml") {
            YAML::Node y = YAML::Load(file);
            for (auto it = y.begin(); it != y.end(); ++it) {
                std::string key = it->first.as<std::string>();
                YAML::Node val = it->second;
                if (val.IsScalar()) {
                    config[key] = val.as<std::string>();
                } else {
                    throw std::runtime_error("Unsupported YAML value type for key: " + key);
                }
            }
        }
        else {
            throw std::runtime_error("Unsupported config file extension: " + ext);
        }
    } catch (const std::exception& e) {
        throw std::runtime_error("Failed to parse config: " + std::string(e.what()));
    }

    apply_defaults(config);
    validate_required_fields(config);
    std::cout << "[CONFIG] Successfully loaded and validated: " << filepath << std::endl;
    return config;
}
