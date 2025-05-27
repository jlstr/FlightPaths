#include <gtest/gtest.h>
#include "./../headers/string_helper.h"
using namespace std;

TEST(StringHelperTest, ConvertsUppercaseToLowercase) {
  EXPECT_EQ(StringHelper::toLower("HELLO"), "hello");
}

TEST(StringHelperTest, LeavesLowercaseUnchanged) {
  EXPECT_EQ(StringHelper::toLower("world"), "world");
}

TEST(StringHelperTest, ConvertsMixedCase) {
  EXPECT_EQ(StringHelper::toLower("HeLLo WoRLD"), "hello world");
}

TEST(StringHelperTest, HandlesNumbersAndSymbols) {
  EXPECT_EQ(StringHelper::toLower("C++20!"), "c++20!");
}

TEST(StringHelperTest, HandlesEmptyString) {
  EXPECT_EQ(StringHelper::toLower(""), "");
}