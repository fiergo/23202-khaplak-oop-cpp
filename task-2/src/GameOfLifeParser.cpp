#include "GameOfLifeParser.h"

bool InputInterpreter::checkFormat(const std::string& string) {
    if (string != "#Life 1.06") {
        return false;
    }
    return true;
}

std::string InputInterpreter::getName(const std::string& string) {
    int start = string.find("#N ") + 3;
    if (start == 2) {
        return "";
    }
    return string.substr(start);
}

std::vector<std::vector<int>> InputInterpreter::getConditions(const std::string& string, bool* parsingErrors) {
    std::vector<std::vector<int>> rules;
    rules.resize(2);
    int start = string.find('B') + 1;
    int end = string.find('/');
    std::string data = string.substr(start, end - start);
    if (start == 0 || end == -1) {
        parsingErrors[2] = true;
        rules[0] = {3};
        rules[1] = {2, 3};
        return rules;
    } else {
        for (const auto &ch: data) {
            if (ch < '0' || ch > '9') {
                continue;
            }
            rules[0].push_back(ch - '0');
        }
    }
    if (rules[0].empty()) {
        rules[0] = {3};
    }
    start = string.find('S') + 1;
    if (start == 0) {
        parsingErrors[2] = true;
        rules[1] = {2, 3};
        return rules;
    } else {
        data = string.substr(start);
        for (const auto &ch: data) {
            if (ch < '0' || ch > '9') {
                continue;
            }
            rules[1].push_back(ch - '0');
        }
    }
    if (rules[1].empty()) {
        rules[1] = {2, 3};
    }
    return rules;
}

std::vector<int> InputInterpreter::getCell(const std::string& string) {
    std::vector<int> res;
    res.resize(2);
    res[0] = 0;
    res[1] = 0;
    int index = 0;
    int digit = 1;
    for (const char& ch : string) {
        if (ch == ' ') {
            ++index;
            digit = 1;
            continue;
        }
        if (ch > '9' || ch < '0') {
            continue;
        }
        res[index] = ch - '0' + res[index] * digit;
        digit *= 10;
    }
    return res;
}

std::vector<int> InputInterpreter::getSize(const std::string& string, bool* parsingErrors) {
    std::vector<int> res;
    res.resize(2);
    int start = string.find('C') + 1;
    int end = string.find('/');
    if (start == 0 || end == -1) {
        res[0] = 50;
        res[1] = 50;
        parsingErrors[3] = true;
        return res;
    } else {
        int column = std::stoi(string.substr(start, end - start));
        res[0] = column;
    }
    start = string.find('R') + 1;
    if (start == 0) {
        res[1] = 50;
        parsingErrors[3] = true;
        return res;
    } else {
        int row = std::stoi(string.substr(start));
        res[1] = row;
    }
    return res;
}

void Parser::processName(std::string& fileLine, bool *parsingErrors, bool& isSuccessGetLine, std::string& universeName) {
    InputInterpreter inputInterpreter;
    universeName = inputInterpreter.getName(fileLine);
    if (universeName.empty()) {
        parsingErrors[1] = true;
        universeName = "NO_NAME";
        isSuccessGetLine = false;
    }
}

void Parser::processConditions(std::string& fileLine, bool *parsingErrors, bool& isSuccessGetLine, std::vector<int>& birthCondition,
                               std::vector<int>& survivalCondition) {
    InputInterpreter inputInterpreter;
    std::vector<std::vector<int>> rules =  inputInterpreter.getConditions(fileLine, parsingErrors);
    if (parsingErrors[2]) {
        isSuccessGetLine = false;
    } else {
        isSuccessGetLine = true;
    }
    birthCondition = rules[0];
    survivalCondition = rules[1];
}

void Parser::processSize(std::string& fileLine, bool *parsingErrors, bool& isSuccessGetLine,
                         int& column, int& row, Grid& grid) {
    InputInterpreter inputInterpreter;
    std::vector<int> size = inputInterpreter.getSize(fileLine, parsingErrors);
    if (parsingErrors[3]) {
        isSuccessGetLine = false;
    } else {
        isSuccessGetLine = true;
    }
    column = size[0];
    row = size[1];
    grid = Grid(size[0], size[1]);
}

void Parser::processCells(std::string& fileLine, bool *parsingErrors, bool& isSuccessGetLine,
                          int& column, int& row, Grid& grid) {
    InputInterpreter inputInterpreter;
    std::vector<int> cells = inputInterpreter.getCell(fileLine);
    if (cells[0] < 0 || cells[1] < 0) {
        parsingErrors[4] = true;
        if (cells[0] < 0) {
            while(cells[0] < 0) {
                cells[0] += column;
            }
        }
        if (cells[1] < 0) {
            while(cells[1] < 0) {
                cells[1] += row;
            }
        }
    }
    grid.setElement(cells[0], cells[1]);
    isSuccessGetLine = true;
}

ParseFileStatus LifeGameParser::parseLifeFile(int argc, char **argv, bool *parsingErrors) {
    if (!argv[1]) {
        return ParseFileStatus::GENERATE;
    }
    FileReader fileReader = FileReader(argv[1]);
    InputInterpreter inputInterpreter;
    // Incorrect format
    if (!inputInterpreter.checkFormat(fileReader.getLine())) {
        return ParseFileStatus::NO_FORMAT;
    }
    // Flag string
    bool isSuccessGetLine = true;
    // Get universe name
    std::string fileLine;
    Parser parser;
    fileLine = fileReader.getLine();
    parser.processName(fileLine, parsingErrors, isSuccessGetLine, universeName);
    // Get birth and survival conditions
    if (isSuccessGetLine) {
        fileLine = fileReader.getLine();
    }
    parser.processConditions(fileLine, parsingErrors, isSuccessGetLine, birthCondition, survivalCondition);
    // Get the grid size
    if (isSuccessGetLine) {
        fileLine = fileReader.getLine();
    }
    parser.processSize(fileLine, parsingErrors, isSuccessGetLine, column, row, grid);
    // Get alive cells
    while (true) {
        if (isSuccessGetLine) {
            fileLine = fileReader.getLine();
        }
        if (fileLine.empty()) {
            break;
        }
        parser.processCells(fileLine, parsingErrors, isSuccessGetLine, column, row, grid);
    }
    if (argc > 2) {
        filename = "out";
        iterationsOffline = 1;
        processConsole(argc, argv, iterationsOffline, filename);
        return ParseFileStatus::OFFLINE;
    }
    return ParseFileStatus::ONLINE;
}

std::vector<int> LifeGameParser::getBirthCondition() const {
    return birthCondition;
}

std::vector<int> LifeGameParser::getSurvivalCondition() const {
    return survivalCondition;
}

int LifeGameParser::getRow() const {
    return row;
}

int LifeGameParser::getColumn() const {
    return column;
}

Grid LifeGameParser::getGrid() const {
    return grid;
}

std::string LifeGameParser::getUniverseName() const {
    return universeName;
}

void LifeGameParser::processConsole(int argc, char** argv, int& iterations, std::string& filename) {
    iterations = 1;
    filename = "out";
    for (int i = 0; i < argc; ++i) {
        if (strlen(argv[i]) < 2) {
            return;
        }
        if (argv[i][0] == '-' && argv[i][1] == 'i') {
            ++i;
            if (argv[i][0] > '9' || argv[i][0] < '0') {
                throw 1;
            }
            iterations = std::stoi(argv[i]);
        }
        if (argv[i][0] == '-' && argv[i][1] == 'o') {
            ++i;
            filename = argv[i];
        }
        if (argv[i][0] == '-' && argv[i][1] == '-') {
            std::string string = argv[i];
            std::string command = string.substr(2, string.find('=') - 2);
            if (command == "iterations") {
                if (string[string.find('=') + 1] > '9' || string[string.find('=') + 1] < '0') {
                    throw 1;
                }
                iterations = std::stoi(string.substr(string.find('=') + 1));
            }
            else if (command == "output") {
                filename = string.substr(string.find('=') + 1);
            }
        }
    }
}

int LifeGameParser::getIterationsOffline() const {
    return iterationsOffline;
}

std::string LifeGameParser::getFilename() const {
    return filename;
}