#include <gtest/gtest.h>
#include <fstream>
#include <string>
#include <map>
#include <variant>
#include <sstream>
#include "config_loader.hpp"

using namespace std;
using namespace sdk::config;  // Use the correct namespace

class ConfigLoaderTest : public ::testing::Test {
protected:
    string test_dir;
    
    void SetUp() override {
        test_dir = "test_files/";
        
        // Create test directory if it doesn't exist
        system(("mkdir -p " + test_dir).c_str());
        
        // Create test files
        write_file(test_dir + "valid.json", R"({
            "port": 8080,
            "debug": true,
            "name": "test_server"
        })");
        
        write_file(test_dir + "valid.yaml", R"(
port: 9090
debug: false
name: "yaml_server"
)");
        
        write_file(test_dir + "missing.json", R"({
            "port": 3000
        })");
        
        write_file(test_dir + "invalid.json", "{ invalid json content");
    }
    
    void TearDown() override {
        // Clean up test files
        system(("rm -rf " + test_dir).c_str());
    }
    
    void write_file(const string& path, const string& content) {
        ofstream file(path);
        file << content;
        file.close();
    }
    
    // Helper function to safely get values from ConfigMap
    template<typename T>
    T get_config_value(const ConfigMap& config, const string& key) {
        auto it = config.find(key);
        if (it == config.end()) {
            throw std::runtime_error("Key not found: " + key);
        }
        
        const auto& variant_value = it->second;
        
        if (std::holds_alternative<T>(variant_value)) {
            return std::get<T>(variant_value);
        }
        
        throw std::runtime_error("Type mismatch for key: " + key);
    }
};

TEST_F(ConfigLoaderTest, ValidJSONLoadsSuccessfully) {
    auto cfg = ConfigLoader::load(test_dir + "valid.json");
    
    EXPECT_EQ(get_config_value<int>(cfg, "port"), 8080);
    EXPECT_EQ(get_config_value<bool>(cfg, "debug"), true);
    EXPECT_EQ(get_config_value<string>(cfg, "name"), "test_server");
}

TEST_F(ConfigLoaderTest, ValidYAMLLoadsSuccessfully) {
    auto cfg = ConfigLoader::load(test_dir + "valid.yaml");
    
    EXPECT_EQ(get_config_value<int>(cfg, "port"), 9090);
    EXPECT_EQ(get_config_value<bool>(cfg, "debug"), false);
    EXPECT_EQ(get_config_value<string>(cfg, "name"), "yaml_server");
}

TEST_F(ConfigLoaderTest, DefaultsAreAppliedWhenMissing) {
    auto cfg = ConfigLoader::load(test_dir + "missing.json");
    
    EXPECT_EQ(get_config_value<int>(cfg, "port"), 3000);
    // Only port is present in the missing.json file
    EXPECT_EQ(cfg.size(), 1);
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
