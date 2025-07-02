// test/c++/test_config_loader.cpp

#include <gtest/gtest.h>
#include <fstream>
#include <string>
#include <map>
#include <variant>
#include "config_loader.hpp"

using namespace std;

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
    EXPECT_EQ(std::get<int>(cfg["module.port"]), 9090);
    EXPECT_EQ(std::get<string>(cfg["environment.mode"]), "prod");
    EXPECT_EQ(std::get<string>(cfg["paths.log_dir"]), "/var/log/atrop");
}

TEST_F(ConfigLoaderTest, ValidYAMLLoadsSuccessfully) {
    auto cfg = ConfigLoader::load(test_dir + "valid.yaml");
    EXPECT_EQ(std::get<int>(cfg["module.port"]), 9091);
    EXPECT_EQ(std::get<string>(cfg["environment.mode"]), "dev");
    EXPECT_EQ(std::get<string>(cfg["paths.log_dir"]), "/tmp/logs");
}

TEST_F(ConfigLoaderTest, DefaultsAreAppliedWhenMissing) {
    auto cfg = ConfigLoader::load(test_dir + "missing.json");
    EXPECT_EQ(std::get<int>(cfg["module.port"]), 8080);  // fallback
    EXPECT_EQ(std::get<string>(cfg["paths.log_dir"]), "./logs");
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
