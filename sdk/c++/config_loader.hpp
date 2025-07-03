#pragma once

#include <string>
#include <map>
#include <variant>
#include <stdexcept>
#include <fstream>

// youll need to add nlohmann/json and yaml-cpp to your vcpkg/CMakeLists dependencies
#include <nlohmann/json.hpp>
#include <yaml-cpp/yaml.h>

namespace sdk {
namespace config {

/// A map of config-keys to either int, bool or string
using ConfigMap = std::map<std::string, std::variant<int,bool,std::string>>;

class ConfigLoader {
public:
  /// Load JSON or YAML file from disk
  /// \throws std::runtime_error on parse error or missing file
  static ConfigMap load(const std::string& path);
};

} // namespace config
} // namespace sdk
