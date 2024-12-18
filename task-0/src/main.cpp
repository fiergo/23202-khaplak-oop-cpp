#include "FileReader.h"
#include "TextParser.h"
#include "WordStatistics.h"
#include "FileWriter.h"
#include <sstream>

int main(int argc, char** argv) {
    if (argv[1] == nullptr || argv[2] == nullptr) {
        return 1;
    }
    FileReader fileReader = FileReader(argv[1]);
    TextParser textParser;
    WordStatistics WordStatistics;

    while (!fileReader.isNextEOF()) {
        std::string stringToParse = fileReader.getLine();
        std::list<std::string> line = textParser.parseString(stringToParse);
        for (const auto& i : line) {
            WordStatistics.addWord(i);
        }
    }
    fileReader.close();

    FileWriter fileWriter = FileWriter(argv[2]);
    for (const auto& i : WordStatistics.getStatistic()) {
        std::vector<std::string> ss;
        ss.push_back(i.word);
        ss.push_back(std::to_string(i.data));
        ss.push_back(std::to_string(i.percentage));
        fileWriter.printString(ss);
    }
    fileWriter.close();
    return 0;
}