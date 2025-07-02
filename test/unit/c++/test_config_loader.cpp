#include <gtest/gtest.h>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <variant>
#include <iostream>

#include "config_loader.hpp"

class ConfigLoaderTest : public ::testing::Test {
protected:
    std::string base_dir = "test/unit/config";

    std::string path(const std::string& filename) {
        return base_dir + "/" + filename;
    }

    std::string to_string(const ConfigValue& value) {
        return std::visit([](auto&& arg) -> std::string {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<T, std::string>) return arg;
            else if constexpr (std::is_same_v<T, int>) return std::to_string(arg);
            else if constexpr (std::is_same_v<T, double>) return std::to_string(arg);
            else if constexpr (std::is_same_v<T, bool>) return arg ? "true" : "false";
            else return "UNKNOWN";
        }, value);
    }
};

TEST_F(ConfigLoaderTest, ValidJSONLoadsSuccessfully) {
    auto config = ConfigLoader::load(path("valid.json"));
    EXPECT_EQ(std::get<int>(config["module.port"]), 9000);
    EXPECT_EQ(to_string(config["environment.mode"]), "prod");
    EXPECT_EQ(to_string(config["paths.log_dir"]), "/var/log/atrop");
}

TEST_F(ConfigLoaderTest, ValidYAMLLoadsSuccessfully) {
    auto config = ConfigLoader::load(path("valid.yaml"));
    EXPECT_EQ(std::get<int>(config["module.timeout"]), 20);
    EXPECT_EQ(to_string(config["module.log_level"]), "DEBUG");
}

TEST_F(ConfigLoaderTest, DefaultsAreAppliedWhenMissing) {
    auto config = ConfigLoader::load(path("missing.json"));
    EXPECT_EQ(std::get<int>(config["module.port"]), 8080);
    EXPECT_EQ(to_string(config["module.log_level"]), "INFO");
}

TEST_F(ConfigLoaderTest, ThrowsOnInvalidFormat) {
    EXPECT_THROW({
        ConfigLoader::load(path("invalid.json"));
    }, std::exception);
}

TEST_F(ConfigLoaderTest, ThrowsOnNonexistentFile) {
    EXPECT_THROW({
        ConfigLoader::load(path("does_not_exist.yaml"));
    }, std::exception);
}
