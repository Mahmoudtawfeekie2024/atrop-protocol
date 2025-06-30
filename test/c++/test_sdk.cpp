#include <gtest/gtest.h>

TEST(SdkTest, BasicCheck) {
    EXPECT_EQ(1 + 1, 2);
}

TEST(SdkTest, StringCompare) {
    std::string expected = "ATROP";
    std::string actual = "ATROP";
    EXPECT_EQ(expected, actual);
}
