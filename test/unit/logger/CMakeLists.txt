add_executable(logger_test
    test_logger.cpp
    ../../../common/logger.cpp
)

target_include_directories(logger_test PRIVATE ../../../common)
target_link_libraries(logger_test PRIVATE spdlog GTest::gtest_main)

add_test(NAME cpp_logger_test COMMAND logger_test)
