// sdk/c++/config_loader.cpp

#include "config_loader.hpp"
#include <nlohmann/json.hpp>
#include <yaml-cpp/yaml.h>
#include <fstream>
#include <stdexcept>

using json = nlohmann::json;

std::map<std::string, ConfigValue> ConfigLoader::load(const std::string& filepath) {
    std::map<std::string, ConfigValue> config;
    std::ifstream file(filepath);

    if (!file.is_open()) {
        throw std::runtime_error("Config file not found: " + filepath);
    }

    if (filepath.ends_with(".json")) {
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
    else if (filepath.ends_with(".yaml") || filepath.ends_with(".yml")) {
        YAML::Node y = YAML::Load(file);
        for (auto it = y.begin(); it != y.end(); ++it) {
            std::string key = it->first.as<std::string>();
            YAML::Node val = it->second;
            if (val.IsScalar()) {
                config[key] = val.as<std::string>();  // Keep as string to simplify
            } else {
                throw std::runtime_error("Unsupported YAML value type for key: " + key);
            }
        }
    }
    else {
        throw std::runtime_error("Unsupported config file extension: " + filepath);
    }

    return config;
}
