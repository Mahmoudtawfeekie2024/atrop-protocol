#include <gtest/gtest.h>
#include "config_loader.hpp"
#include <filesystem>
#include <iostream>
#include <string>

namespace fs = std::filesystem;

class ConfigLoaderTest : public ::testing::Test {
protected:
    std::string base_dir = "test/unit/config";

    std::string path(const std::string& file) {
        return (fs::path(base_dir) / file).string();
    }

    void expect_config_value(const std::map<std::string, ConfigValue>& config, const std::string& key, const ConfigValue& expected) {
        ASSERT_TRUE(config.count(key)) << "Missing key: " << key;
        std::visit([&](const auto& actual_val) {
            EXPECT_EQ(actual_val, std::get<decltype(actual_val)>(expected)) << "Key: " << key;
        }, config.at(key));
    }
};

TEST_F(ConfigLoaderTest, ValidJSONLoadsSuccessfully) {
    auto config = ConfigLoader::load(path("valid.json"));
    expect_config_value(config, "module.port", 9000);
    expect_config_value(config, "environment.mode", std::string("prod"));
    expect_config_value(config, "paths.log_dir", std::string("/var/log/atrop"));
}

TEST_F(ConfigLoaderTest, ValidYAMLLoadsSuccessfully) {
    auto config = ConfigLoader::load(path("valid.yaml"));
    expect_config_value(config, "module.timeout", 20);
    expect_config_value(config, "module.log_level", std::string("DEBUG"));
}

TEST_F(ConfigLoaderTest, DefaultsAreAppliedWhenMissing) {
    auto config = ConfigLoader::load(path("missing.json"));
    expect_config_value(config, "module.port", 8080);  // default
    expect_config_value(config, "paths.model_dir", std::string("./models"));  // default
}

TEST_F(ConfigLoaderTest, ThrowsOnInvalidFormat) {
    EXPECT_THROW(ConfigLoader::load(path("invalid.json")), std::runtime_error);
}

TEST_F(ConfigLoaderTest, ThrowsOnNonexistentFile) {
    EXPECT_THROW(ConfigLoader::load("nonexistent.json"), std::runtime_error);
}

// --- New tests for instance API ---

TEST_F(ConfigLoaderTest, InstanceHasAndGetMethodsWork) {
    ConfigLoader loader(path("valid.json"));
    EXPECT_TRUE(loader.has("module.port"));
    EXPECT_TRUE(loader.has("environment.mode"));
    EXPECT_FALSE(loader.has("nonexistent.key"));

    EXPECT_EQ(loader.get<int>("module.port"), 9000);
    EXPECT_EQ(loader.get<std::string>("environment.mode"), "prod");
    EXPECT_EQ(loader.get<std::string>("paths.log_dir"), "/var/log/atrop");
}

TEST_F(ConfigLoaderTest, InstanceGetThrowsOnMissingKey) {
    ConfigLoader loader(path("valid.json"));
    EXPECT_THROW(loader.get<int>("nonexistent.key"), std::out_of_range);
}

TEST_F(ConfigLoaderTest, InstanceGetThrowsOnWrongType) {
    ConfigLoader loader(path("valid.json"));
    // module.port is int, so getting as string should throw
    EXPECT_THROW(loader.get<std::string>("module.port"), std::bad_variant_access);
}
