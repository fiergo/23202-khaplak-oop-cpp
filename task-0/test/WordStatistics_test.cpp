#include "gtest/gtest.h"
#include "../src/WordStatistics.h"
#include <list>
#include <vector>

TEST(WordStatisticsTest, EmptyWordList) {
    WordStatistics stats;
    std::list<WordFrequency> result = stats.getStatistic();
    ASSERT_TRUE(result.empty());
}


TEST(WordStatisticsTest, SingleWord) {
    WordStatistics stats;
    stats.addWord("hello");
    std::list<WordFrequency> result = stats.getStatistic();

    ASSERT_EQ(result.size(), 1);
    ASSERT_EQ(result.front().word, "hello");
    ASSERT_EQ(result.front().data, 1);
    ASSERT_DOUBLE_EQ(result.front().percentage, 100.0);
}


TEST(WordStatisticsTest, MultipleWords) {
    WordStatistics stats;
    stats.addWord("apple");
    stats.addWord("banana");
    stats.addWord("apple");
    stats.addWord("orange");
    stats.addWord("banana");
    stats.addWord("apple");

    std::list<WordFrequency> result = stats.getStatistic();

    std::vector<WordFrequency> result_vector(result.begin(), result.end());

    ASSERT_EQ(result_vector.size(), 3);
    ASSERT_EQ(result_vector[0].word, "apple");
    ASSERT_EQ(result_vector[0].data, 3);
    ASSERT_DOUBLE_EQ(result_vector[0].percentage, 50.0);
    ASSERT_EQ(result_vector[1].word, "banana");
    ASSERT_EQ(result_vector[1].data, 2);
    ASSERT_DOUBLE_EQ(result_vector[1].percentage, 33.333333333333336);
    ASSERT_EQ(result_vector[2].word, "orange");
    ASSERT_EQ(result_vector[2].data, 1);
    ASSERT_DOUBLE_EQ(result_vector[2].percentage, 16.666666666666668);

}


TEST(WordStatisticsTest, WordsWithSameFrequency) {
    WordStatistics stats;
    stats.addWord("cat");
    stats.addWord("dog");
    stats.addWord("cat");
    stats.addWord("dog");
    stats.addWord("pig");
    stats.addWord("pig");

    std::list<WordFrequency> result = stats.getStatistic();
    std::vector<WordFrequency> result_vector(result.begin(), result.end());

    ASSERT_EQ(result_vector.size(), 3);
    ASSERT_EQ(result_vector[0].word, "cat");
    ASSERT_EQ(result_vector[0].data, 2);
    ASSERT_DOUBLE_EQ(result_vector[0].percentage, 33.333333333333336);
    ASSERT_EQ(result_vector[1].word, "dog");
    ASSERT_EQ(result_vector[1].data, 2);
    ASSERT_DOUBLE_EQ(result_vector[1].percentage, 33.333333333333336);
    ASSERT_EQ(result_vector[2].word, "pig");
    ASSERT_EQ(result_vector[2].data, 2);
    ASSERT_DOUBLE_EQ(result_vector[2].percentage, 33.333333333333336);
}


TEST(WordStatisticsTest, AddMultipleWordAndGetStatistics) {
    WordStatistics stats;
    stats.addWord("apple");
    stats.addWord("banana");
    stats.addWord("apple");
    stats.addWord("orange");
    stats.addWord("banana");
    stats.addWord("apple");

    std::list<WordFrequency> result = stats.getStatistic();

    std::vector<WordFrequency> result_vector(result.begin(), result.end());

    ASSERT_EQ(result_vector.size(), 3);
    ASSERT_EQ(result_vector[0].word, "apple");
    ASSERT_EQ(result_vector[0].data, 3);
    ASSERT_DOUBLE_EQ(result_vector[0].percentage, 50.0);
    ASSERT_EQ(result_vector[1].word, "banana");
    ASSERT_EQ(result_vector[1].data, 2);
    ASSERT_DOUBLE_EQ(result_vector[1].percentage, 33.333333333333336);
    ASSERT_EQ(result_vector[2].word, "orange");
    ASSERT_EQ(result_vector[2].data, 1);
    ASSERT_DOUBLE_EQ(result_vector[2].percentage, 16.666666666666668);
}


TEST(WordStatisticsTest, CaseSensitivity) {
    WordStatistics stats;
    stats.addWord("Apple");
    stats.addWord("apple");
    std::list<WordFrequency> result = stats.getStatistic();

    std::vector<WordFrequency> result_vector(result.begin(), result.end());
    ASSERT_EQ(result_vector.size(), 2);
    ASSERT_EQ(result_vector[0].word, "apple");
    ASSERT_EQ(result_vector[0].data, 1);
    ASSERT_DOUBLE_EQ(result_vector[0].percentage, 50.0);
    ASSERT_EQ(result_vector[1].word, "Apple");
    ASSERT_EQ(result_vector[1].data, 1);
    ASSERT_DOUBLE_EQ(result_vector[1].percentage, 50.0);
}
