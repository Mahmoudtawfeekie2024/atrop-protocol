#include <gtest/gtest.h>
#include <fstream>
#include <string>
#include <map>
#include <variant>
#include <sstream>
#include "config_loader.hpp"

using namespace std;

// Utility: Extract value from variant with optional type conversion
template<typename T>
T get_variant_as(const ConfigValue& v) {
    if (std::holds_alternative<T>(v)) {
        return std::get<T>(v);
    }
    if constexpr (std::is_same_v<T, int>) {
        if (std::holds_alternative<std::string>(v)) {
            return std::stoi(std::get<std::string>(v));
        }
    } else if constexpr (std::is_same_v<T, std::string>) {
        if (std::holds_alternative<int>(v)) {
            return std::to_string(std::get<int>(v));
        }
    }
    throw std::runtime_error("Incompatible type in variant");
}

class ConfigLoaderTest : public ::testing::Test {
protected:
    string test_dir = "test/unit/config/";

    void write_file(const string& filename, const string& content) {
        ofstream file(test_dir + filename);
        file << content;
        file.close();
    }

    void SetUp() override {
        system(("mkdir -p " + test_dir).c_str());

        write_file("valid.json", R"({
            "module.port": 9090,
            "environment.mode": "prod",
            "paths.log_dir": "/var/log/atrop"
        })");

        write_file("valid.yaml", R"(
module.port: 9091
environment.mode: "dev"
paths.log_dir: "/tmp/logs"
)");

        write_file("invalid.json", R"({
            "module.port": 8080,
            "module.timeout":   // missing value
        })");

        write_file("missing.json", R"({
            "module.timeout": 30
        })");
    }
};

TEST_F(ConfigLoaderTest, ValidJSONLoadsSuccessfully) {
    auto cfg = ConfigLoader::load(test_dir + "valid.json");
    EXPECT_EQ(get_variant_as<int>(cfg["module.port"]), 9090);
    EXPECT_EQ(get_variant_as<string>(cfg["environment.mode"]), "prod");
    EXPECT_EQ(get_variant_as<string>(cfg["paths.log_dir"]), "/var/log/atrop");
}

TEST_F(ConfigLoaderTest, ValidYAMLLoadsSuccessfully) {
    auto cfg = ConfigLoader::load(test_dir + "valid.yaml");
    EXPECT_EQ(get_variant_as<int>(cfg["module.port"]), 9091);
    EXPECT_EQ(get_variant_as<string>(cfg["environment.mode"]), "dev");
    EXPECT_EQ(get_variant_as<string>(cfg["paths.log_dir"]), "/tmp/logs");
}

TEST_F(ConfigLoaderTest, DefaultsAreAppliedWhenMissing) {
    auto cfg = ConfigLoader::load(test_dir + "missing.json");
    EXPECT_EQ(get_variant_as<int>(cfg["module.port"]), 8080);  // fallback
    EXPECT_EQ(get_variant_as<string>(cfg["paths.log_dir"]), "./logs");
}

TEST_F(ConfigLoaderTest, ThrowsOnInvalidFormat) {
    EXPECT_THROW({
        ConfigLoader::load(test_dir + "invalid.json");
    }, std::runtime_error);
}

TEST_F(ConfigLoaderTest, ThrowsOnNonexistentFile) {
    EXPECT_THROW({
        ConfigLoader::load(test_dir + "not_found.yaml");
    }, std::runtime_error);
}

// --- New tests for instance API ---

TEST_F(ConfigLoaderTest, InstanceHasAndGetMethodsWork) {
    ConfigLoader loader(test_dir + "valid.json");
    EXPECT_TRUE(loader.has("module.port"));
    EXPECT_TRUE(loader.has("environment.mode"));
    EXPECT_FALSE(loader.has("nonexistent.key"));

    EXPECT_EQ(loader.get<int>("module.port"), 9090);
    EXPECT_EQ(loader.get<std::string>("environment.mode"), "prod");
    EXPECT_EQ(loader.get<std::string>("paths.log_dir"), "/var/log/atrop");
}

TEST_F(ConfigLoaderTest, InstanceGetThrowsOnMissingKey) {
    ConfigLoader loader(test_dir + "valid.json");
    EXPECT_THROW(loader.get<int>("nonexistent.key"), std::out_of_range);
}

TEST_F(ConfigLoaderTest, InstanceGetThrowsOnWrongType) {
    ConfigLoader loader(test_dir + "valid.json");
    // module.port is int, so getting as string should throw
    EXPECT_THROW(loader.get<std::string>("module.port"), std::bad_variant_access);
}
