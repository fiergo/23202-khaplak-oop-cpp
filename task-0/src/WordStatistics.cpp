#include "WordStatistics.h"

bool WordStatistics::compare(WordFrequency& word1, WordFrequency& word2) {
    return (word1.data > word2.data);
}

void WordStatistics::createStatisticsList(const std::list<std::string>& wordList) {
    wordsStatistics->clear();
    wordsAmount = wordList.size();
    for (const std::string& i : wordList) {
        WordFrequency wordFrequency = WordFrequency(i, 1, (double) 1 / wordsAmount * 100);
        findPositionInList(wordFrequency);
    }
    wordsStatistics->sort(compare);
}

void WordStatistics::findPositionInList(WordFrequency& wordFrequency) {
    for (WordFrequency& i : *wordsStatistics) {
        if (i.word == wordFrequency.word) {
            i.data++;
            i.percentage = (double)i.data / wordsAmount * 100;
            return;
        }
    }
    (*wordsStatistics).push_back(wordFrequency);
}

std::list<WordFrequency> WordStatistics::getStatistic() {
    if (!wordDict) {
        return {};
    }
    createStatisticsList(*wordDict);
    return *wordsStatistics;
}

WordStatistics::WordStatistics() {
    auto* words = new std::list<WordFrequency>;
    auto* wordDict = new std::list<std::string>;
    this->wordsStatistics = words;
    this->wordDict = wordDict;
    wordsAmount = 0;
}

void WordStatistics::addWord(const std::string& word) {
    wordDict->push_back(word);
}