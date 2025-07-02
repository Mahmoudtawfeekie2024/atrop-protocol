from daemon.logger import setup_logger


using json = nlohmann::json;

TEST(LoggerTest, FlatFileOutputText) {
    std::string filename = "test_log.txt";
    atrop::Logger::init("ATROP.Test", "info", filename);
    auto log = atrop::Logger::get();
    log->info("Flat file log message");

    std::ifstream file(filename);
    std::string line;
    bool found = false;
    while (getline(file, line)) {
        if (line.find("Flat file log message") != std::string::npos) {
            found = true;
            break;
        }
    }
    file.close();
    ASSERT_TRUE(found);
    std::remove(filename.c_str());
}

TEST(LoggerTest, JsonFormatOutput) {
    std::string filename = "json_log.txt";
    atrop::Logger::init("ATROP.Test", "info", filename);
    auto log = atrop::Logger::get();
    log->set_pattern(R"({"ts":"%Y-%m-%d","level":"%l","name":"%n","msg":"%v"})");
    log->info("JSON formatted message");

    std::ifstream file(filename);
    std::string line;
    getline(file, line);
    json parsed = json::parse(line);
    ASSERT_EQ(parsed["msg"], "JSON formatted message");
    ASSERT_EQ(parsed["level"], "INFO");
    file.close();
    std::remove(filename.c_str());
}
