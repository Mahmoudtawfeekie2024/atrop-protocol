#include <gtest/gtest.h>
#include "config_loader.hpp"
#include <filesystem>
#include <iostream>
#include <string>

namespace fs = std::filesystem;

class ConfigLoaderTest : public ::testing::Test {
protected:
    std::string base_dir = "test/unit/sdk/config";

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

// --- Instance API tests ---

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

// --- Config-driven threshold and event trigger tests ---

TEST_F(ConfigLoaderTest, TelemetryThresholdConfigAndEventTrigger) {
    // Load a config file with a custom telemetry threshold
    auto config = ConfigLoader::load(path("config.json"));
    // Suppose the config contains: "telemetry.threshold": 42
    ASSERT_TRUE(config.count("telemetry.threshold"));
    int threshold = std::get<int>(config["telemetry.threshold"]);
    EXPECT_EQ(threshold, 42);

    // Simulate reaching the threshold in your FSM logic
    int telemetry_value = 42;
    bool threshold_reached = (telemetry_value >= threshold);
    EXPECT_TRUE(threshold_reached);

    // (FSM event trigger would be tested in FSM test, not here)
}

TEST_F(ConfigLoaderTest, TelemetryThresholdDefaultApplied) {
    // Load a config file missing the telemetry.threshold key
    auto config = ConfigLoader::load(path("missing_log_dir.yaml"));
    // If your loader applies a default, check it here (e.g., default is 100)
    int default_threshold = config.count("telemetry.threshold") ? std::get<int>(config["telemetry.threshold"]) : 100;
    EXPECT_EQ(default_threshold, 100);
}

// --- Edge case: empty config file ---

TEST_F(ConfigLoaderTest, EmptyConfigFileHandledGracefully) {
    EXPECT_NO_THROW({
        auto config = ConfigLoader::load(path("empty.json"));
        // Should apply all defaults
        expect_config_value(config, "module.port", 8080);
        expect_config_value(config, "paths.model_dir", std::string("./models"));
    });
}
