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

TEST(StringHelperTest, TrimsLeadingSpaces) {
  EXPECT_EQ(StringHelper::trim("   hello"), "hello");
}

TEST(StringHelperTest, TrimsTrailingSpaces) {
  EXPECT_EQ(StringHelper::trim("world   "), "world");
}

TEST(StringHelperTest, TrimsBothLeadingAndTrailingSpaces) {
  EXPECT_EQ(StringHelper::trim("   hello world   "), "hello world");
}

TEST(StringHelperTest, LeavesInternalSpacesUntouched) {
  EXPECT_EQ(StringHelper::trim("   a  b c   "), "a  b c");
}

TEST(StringHelperTest, HandlesStringWithOnlySpaces) {
  EXPECT_EQ(StringHelper::trim("     "), "");
}

TEST(StringHelperTest, HandlesEmptyStringTrimming) {
  EXPECT_EQ(StringHelper::trim(""), "");
}

TEST(StringHelperTest, HandlesTabsAndNewlines) {
  EXPECT_EQ(StringHelper::trim("\t\n  hello\n\t "), "hello");
}

TEST(StringHelperTest, TrimsSingleCharacterStringWithSpace) {
  EXPECT_EQ(StringHelper::trim(" "), "");
}

TEST(StringHelperTest, TrimsSingleNonSpaceCharacter) {
  EXPECT_EQ(StringHelper::trim("x"), "x");
}
