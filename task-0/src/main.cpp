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
    fileWriter.printString("Word;Frequency;Frequency(%)\n");
    for (const auto& i : WordStatistics.getStatistic()) {
        std::stringstream ss;
        ss << i.word << ';' << i.data << ';' << i.percentage << '\n';
        fileWriter.printString(ss.str());
    }
    fileWriter.close();
    return 0;
}