#pragma once
#include <iostream>
#include <sstream>
#include <list>

typedef struct FrequencyOfWord {
    std::string word;
    int data;
    double percentage;

    FrequencyOfWord(const std::string& word, int data, double percentage) : word(word), data(data), percentage(percentage) {}
} WordFrequency;

class WordStatistics
{
private:
    std::list<FrequencyOfWord>* wordsStatistics;
    std::list<std::string>* wordDict;
    int wordsAmount{};
    static bool compare(FrequencyOfWord& word1, FrequencyOfWord& word2);
    void createStatisticsList(const std::list<std::string>& wordList);
    void findPositionInList(FrequencyOfWord& FrequencyOfWord);
public:
    std::list<FrequencyOfWord> getStatistic();
    void addWord(const std::string& word);
    WordStatistics();
};