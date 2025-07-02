#pragma once

#include <memory>
#include <string>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

namespace atrop {

class Logger {
public:
    static void init(const std::string& name, const std::string& level = "info", const std::string& file = "");
    static std::shared_ptr<spdlog::logger> get();

private:
    static std::shared_ptr<spdlog::logger> logger_;
};

} // namespace atrop
