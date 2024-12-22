#include "gtest/gtest.h"
#include "../src/TextParser.h"
#include <list>
#include <string>

TEST(TextParserTest, ParseSimpleLine) {
    TextParser parser;
    std::string line = "This is a simple line.";
    std::list<std::string> expected = {"This", "is", "a", "simple", "line"};
    std::list<std::string> result = parser.parseString(line);
    ASSERT_EQ(result, expected);
}


TEST(TextParserTest, ParseLineWithNumbers) {
    TextParser parser;
    std::string line = "Line 1 with 2 numbers 34.";
    std::list<std::string> expected = {"Line", "1", "with", "2", "numbers", "34"};
    std::list<std::string> result = parser.parseString(line);
    ASSERT_EQ(result, expected);
}


TEST(TextParserTest, ParseLineWithSpecialChars) {
    TextParser parser;
    std::string line = "Hello, world! How are you?";
    std::list<std::string> expected = {"Hello", "world", "How", "are", "you"};
    std::list<std::string> result = parser.parseString(line);
    ASSERT_EQ(result, expected);
}


TEST(TextParserTest, ParseLineWithLeadingAndTrailingSpecialChars) {
    TextParser parser;
    std::string line = ",.  leading and trailing !! special chars  ,;.";
    std::list<std::string> expected = {"leading", "and", "trailing", "special", "chars"};
    std::list<std::string> result = parser.parseString(line);
    ASSERT_EQ(result, expected);

}


TEST(TextParserTest, ParseEmptyLine) {
    TextParser parser;
    std::string line;
    std::list<std::string> expected = {};
    std::list<std::string> result = parser.parseString(line);
    ASSERT_EQ(result, expected);
}


TEST(TextParserTest, ParseLineWithOnlySpecialChars) {
    TextParser parser;
    std::string line = "!!!,,,....";
    std::list<std::string> expected = {};
    std::list<std::string> result = parser.parseString(line);
    ASSERT_EQ(result, expected);
}


TEST(TextParserTest, ParseLineWithCamelCase)
{
    TextParser parser;
    std::string line = "ThisIsACamelCaseString";
    std::list<std::string> expected = {"ThisIsACamelCaseString"};
    std::list<std::string> result = parser.parseString(line);
    ASSERT_EQ(result,expected);
}


TEST(TextParserTest, ParseLineWithMixedCase)
{
    TextParser parser;
    std::string line = "MiXeDCaSeStRiNg";
    std::list<std::string> expected = {"MiXeDCaSeStRiNg"};
    std::list<std::string> result = parser.parseString(line);
    ASSERT_EQ(result,expected);

}


TEST(TextParserTest, ParseLineWithSingleNumber)
{
    TextParser parser;
    std::string line = "12345";
    std::list<std::string> expected = {"12345"};
    std::list<std::string> result = parser.parseString(line);
    ASSERT_EQ(result,expected);
}


TEST(TextParserTest, ParseLineWithSingleChar)
{
    TextParser parser;
    std::string line = "a";
    std::list<std::string> expected = {"a"};
    std::list<std::string> result = parser.parseString(line);
    ASSERT_EQ(result,expected);
}
