#include "logger.hpp"

namespace atrop {

std::shared_ptr<spdlog::logger> Logger::logger_ = nullptr;

void Logger::init(const std::string& name, const std::string& level, const std::string& file) {
    try {
        std::vector<spdlog::sink_ptr> sinks;

        // Console sink
        auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        sinks.push_back(console_sink);

        // Optional file sink
        if (!file.empty()) {
            auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(file, true);
            sinks.push_back(file_sink);
        }

        logger_ = std::make_shared<spdlog::logger>(name, begin(sinks), end(sinks));
        logger_->set_pattern("[%Y-%m-%d %H:%M:%S] [%^%l%$] [%n] %v");

        // Set log level
        logger_->set_level(spdlog::level::from_str(level));
        logger_->flush_on(spdlog::level::warn);

        spdlog::register_logger(logger_);
    } catch (const spdlog::spdlog_ex& ex) {
        std::cerr << "Logger init failed: " << ex.what() << std::endl;
    }
}

std::shared_ptr<spdlog::logger> Logger::get() {
    if (!logger_) {
        init("atrop", "info");  // default fallback
    }
    return logger_;
}

} // namespace atrop
