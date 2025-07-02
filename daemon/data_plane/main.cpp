#include <iostream>
#include <config_loader.hpp>
#include <logger.hpp>

int main() {
    std::cout << "ATROP Data Plane Daemon starting..." << std::endl;

    try {
        auto config = ConfigLoader::load("config.yaml");

        std::string level = std::get<std::string>(config["module.log_level"]);
        std::string format = std::get<std::string>(config["module.log_format"]);
        std::string file = std::get<std::string>(config["module.log_file"]);

        atrop::Logger::init("ATROP.DataPlane", level, file);
        if (format == "json") {
            atrop::Logger::get()->set_pattern(R"({"ts":"%Y-%m-%d %H:%M:%S","level":"%l","name":"%n","msg":"%v"})");
        }

        auto log = atrop::Logger::get();
        log->info("Data plane logger started with level: {}", level);
    } catch (const std::exception& e) {
        std::cerr << "[ERROR] Config or logging failed: " << e.what() << std::endl;
        if (auto log = atrop::Logger::get()) {
            log->error("Exception: {}", e.what());
        }
        return 1;
    }

    return 0;
}
