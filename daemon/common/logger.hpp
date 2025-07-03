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


// ✅ Logging macro aliases
#define LOG_INFO(...)  ::atrop::Logger::get()->info(__VA_ARGS__)
#define LOG_ERROR(...) ::atrop::Logger::get()->error(__VA_ARGS__)
#define LOG_WARN(...)  ::atrop::Logger::get()->warn(__VA_ARGS__)
#define LOG_DEBUG(...) ::atrop::Logger::get()->debug(__VA_ARGS__)
