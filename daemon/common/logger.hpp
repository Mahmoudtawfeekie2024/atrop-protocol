#pragma once

#include <memory>
#include <string>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

namespace atrop {

/**
 * Central ATROP Logger using spdlog.
 * Supports stdout and optional file logging with named instance.
 */
class Logger {
public:
    /**
     * Initialize the logger.
     *
     * @param name  Logger instance name (used in output prefix).
     * @param level Logging level: "info", "debug", "warn", "error"
     * @param file  Optional file path for log output; leave empty for console-only.
     */
    static void init(const std::string& name, const std::string& level = "info", const std::string& file = "");

    /**
     * Access the initialized logger.
     *
     * @return A shared pointer to the spdlog logger.
     */
    static std::shared_ptr<spdlog::logger> get();

private:
    static std::shared_ptr<spdlog::logger> logger_;
};

} // namespace atrop

//  Logging macro aliases  safe for use in all daemon modules including FSM
#define LOG_INFO(...)   ::atrop::Logger::get()->info(__VA_ARGS__)
#define LOG_ERROR(...)  ::atrop::Logger::get()->error(__VA_ARGS__)
#define LOG_WARN(...)   ::atrop::Logger::get()->warn(__VA_ARGS__)
#define LOG_DEBUG(...)  ::atrop::Logger::get()->debug(__VA_ARGS__)
