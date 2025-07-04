// sdk/c++/config_loader.hpp

#pragma once

#include <string>
#include <map>
#include <variant>
#include <stdexcept>
#include <type_traits>

using ConfigValue = std::variant<std::string, int, double, bool>;

class ConfigLoader {
public:
    // Load config as before (static method, backward compatible)
    static std::map<std::string, ConfigValue> load(const std::string& filepath);

    // New: Construct from file (preferred for new code)
    explicit ConfigLoader(const std::string& filepath);

    // New: Check if key exists
    bool has(const std::string& key) const;

    // New: Get value as type T (throws if not found or wrong type)
    template<typename T>
    T get(const std::string& key) const {
        auto it = config_.find(key);
        if (it == config_.end()) {
            throw std::out_of_range("Config key not found: " + key);
        }
        if (!std::holds_alternative<T>(it->second)) {
            throw std::bad_variant_access();
        }
        return std::get<T>(it->second);
    }

    // New: Get raw config map (for compatibility)
    const std::map<std::string, ConfigValue>& raw() const { return config_; }

private:
    std::map<std::string, ConfigValue> config_;
};
