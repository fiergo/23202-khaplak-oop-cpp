//
// Created by MV on 06.10.2024.
//

#ifndef TASK_0_TEST1_H
#define TASK_0_TEST1_H

#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <list>

class countWord {
    int count;
    std::map<std::string, int> wordMap;

public:
    countWord();

    void readingAndCounting(std::string nameInputFile);

    void sortDataAndWriteToCSV(std::string nameOutputFile);

private:

    void writeToCSV(std::list<std::pair<std::string, int>> listPair, std::string nameOutputFile);
};

#endif //TASK_0_TEST1_H
