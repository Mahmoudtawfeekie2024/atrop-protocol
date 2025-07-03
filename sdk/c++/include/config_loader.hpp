// sdk/c++/include/config_loader.hpp
#pragma once

//
//
// A simple loader for JSON/YAML configuration files into a flat map<string,ConfigValue>,
// with defaults applied and minimal validation.
// 

#include <string>
#include <map>
#include <variant>
#include <stdexcept>

namespace sdk {

/// A configuration value may be one of these scalar types.
using ConfigValue = std::variant<std::string, int, double, bool>;

/// The ConfigLoader class provides a single entry point to load a .json/.yaml/.yml
/// file into a key→ConfigValue map, apply defaults, and validate required fields.
///
/// Usage:
///   auto cfg = sdk::ConfigLoader::load("config.yaml");
///   int port = std::get<int>(cfg["module.port"]);
///
/// Throws std::runtime_error on file-not-found, parse errors, missing required fields, etc.
class ConfigLoader {
public:
    /// Load a configuration file (".json", ".yaml" or ".yml").
    /// Returns a flat map of key→value pairs.
    /// 
    /// @param filepath  path to your .json or .yaml configuration
    /// @return           std::map<std::string,ConfigValue> with all keys, including defaults
    /// @throws std::runtime_error on any error (I/O, parse, validation)
    static std::map<std::string, ConfigValue> load(const std::string& filepath);
};

/// Convenience wrapper so you can simply write:
///   auto cfg = sdk::load_config("my_config.json");
/// instead of calling ConfigLoader directly.
inline std::map<std::string, ConfigValue> load_config(const std::string& filepath) {
    return ConfigLoader::load(filepath);
}

} // namespace sdk
