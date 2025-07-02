// sdk/c++/config_loader.hpp

#pragma once

#include <string>
#include <map>
#include <variant>

using ConfigValue = std::variant<std::string, int, double, bool>;

class ConfigLoader {
public:
    static std::map<std::string, ConfigValue> load(const std::string& filepath);
};
