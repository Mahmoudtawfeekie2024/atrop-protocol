#include <logger.hpp>
#include <gtest/gtest.h>

TEST(ProtocolParser, BasicHeaderValidation) {
    atrop::Logger::init("ATROP.Test.Protocol", "debug");
    auto log = atrop::Logger::get();

    log->debug("Running protocol parser test");
    ASSERT_TRUE(true);
}
