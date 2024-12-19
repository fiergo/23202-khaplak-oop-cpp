#include "LifeGame.h"

void LifeGame::runOffline() {
    GameEngine gameEngine = GameEngine(grid, birthCondition,survivalCondition);
    grid = gameEngine.computeIterations(iterationsOffline);
    filename += ".life";
    createLifeFile(filename);
}

void LifeGame::runOnline() {
    GameEngine gameEngine = GameEngine(grid, birthCondition,survivalCondition);
    Interface interface;
    GameStatus gameStatus = GameStatus::CONTINUE;
    while (gameStatus == GameStatus::CONTINUE) {
        interface.printInterface(grid.getGrid(), birthCondition, survivalCondition, universeName, iterationNum, parsingErrors);
        Cmd cmd = interface.getCommand();
        gameStatus = processCmd(cmd, gameEngine);
    }
}

void LifeGame::startGame() {
    if (parseFileStatus == ParseFileStatus::NO_FORMAT) {
        std::cout << "ERROR: WRONG FILE FORMAT.\nPress any button to continue...";
        std::getchar();
        return;
    }
    // Offline mode
    if (parseFileStatus == ParseFileStatus::OFFLINE) {

        runOffline();
        return;
    }
    // Online mode
    if (parseFileStatus == ParseFileStatus::GENERATE) {
        generateUniverse();
    }
    runOnline();
}

GameStatus LifeGame::processCmd(Cmd cmd, GameEngine& gameEngine) {
    std::string name = cmd.getName();
    std::string attributes = cmd.getAttributes();
    if (cmd.getName() == "exit") {
        return GameStatus::EXIT;
    }
    if (cmd.getName() == "tick" || cmd.getName() == "t") {
        attributes = attributes.substr(attributes.find('=') + 1, attributes.find('>') - attributes.find('=') + 1);
        if (attributes[0] > '9' || attributes[0] < '0') {
            callHelp();
            return GameStatus::CONTINUE;
        }
        int attributesInt = std::stoi(attributes);
        iterationNum += attributesInt;
        grid = gameEngine.computeIterations(attributesInt);
    }
    else if (cmd.getName() == "dump") {
        std::string filename = attributes.substr(attributes.find('<') +1, attributes.find('>') - attributes.find('<') - 1) + ".life";
        createLifeFile(filename);
    }
    else {
        callHelp();
    }
    return GameStatus::CONTINUE;
}

void LifeGame::createLifeFile(const std::string& filename) {
    FileWriter fileWriter = FileWriter(filename);
    std::vector<std::string> ss;
    // File format
    ss.push_back("#Life 1.06\n");
    // Universe name
    ss.push_back("#N " + universeName + '\n');
    // Universe rules
    ss.push_back("#R ");
    std::string string;
    ss.push_back("B");
    for (const int i : birthCondition) {
        string += i + '0';
    }
    string += "/S";
    for (const int i : survivalCondition) {
        string += i + '0';
    }
    ss.push_back(string + '\n');
    // Universe size
    ss.push_back( "#S C");
    ss.push_back(std::to_string(column));
    ss.push_back( "/R");
    ss.push_back(std::to_string(row) + '\n');
    // Alive cells
    for (int i = 0; i < grid.getRow(); ++i) {
        for (int j = 0; j < grid.getColumn(); ++j) {
            if (grid.getElement(j, i)) {
                ss.push_back(std::to_string(j) + " " + std::to_string(i) + '\n');
            }
        }
    }
    fileWriter.printString(ss);
    fileWriter.close();
}

void LifeGame::callHelp() {
    Interface interface;
    interface.printHelp();
    std::getchar();
}

void LifeGame::generateUniverse() {
    column = DEFAULT_SIZE;
    row = DEFAULT_SIZE;
    grid = Grid(DEFAULT_SIZE,DEFAULT_SIZE);
    grid = Grid(DEFAULT_SIZE,DEFAULT_SIZE);
    birthCondition = {3};
    survivalCondition = {2,3};
    universeName = "Glider Gun";
    Generator generator;
    generator.createGliderGun(grid);
}

LifeGame::LifeGame(std::vector<int> birthCondition, std::vector<int> survivalCondition, int row, int column, Grid grid,
                   std::string universeName, ParseFileStatus parseFileStatus, bool* parseLifeFileStatus,
                   std::string filename, int iterationsOffline) {
    this->birthCondition = birthCondition;
    this->survivalCondition = survivalCondition;
    this->row = row;
    this->column = column;
    this->grid = grid;
    this->universeName = universeName;
    this->parseFileStatus = parseFileStatus;
    this->filename = filename;
    this->iterationsOffline = iterationsOffline;
    this->parsingErrors = parseLifeFileStatus;
}

void Generator::createGliderGun(Grid &grid) {
    grid.setElement(1, 5);
    grid.setElement(1, 6);
    grid.setElement(2, 5);
    grid.setElement(2, 6);
    grid.setElement(11, 5);
    grid.setElement(11, 6);
    grid.setElement(11, 7);
    grid.setElement(12, 4);
    grid.setElement(12, 8);
    grid.setElement(13, 3);
    grid.setElement(13, 9);
    grid.setElement(14, 3);
    grid.setElement(14, 9);
    grid.setElement(15, 6);
    grid.setElement(16, 4);
    grid.setElement(16, 8);
    grid.setElement(17, 5);
    grid.setElement(17, 6);
    grid.setElement(17, 7);
    grid.setElement(18, 6);
    grid.setElement(21, 3);
    grid.setElement(21, 4);
    grid.setElement(21, 5);
    grid.setElement(22, 3);
    grid.setElement(22, 4);
    grid.setElement(22, 5);
    grid.setElement(23, 2);
    grid.setElement(23, 6);
    grid.setElement(25, 1);
    grid.setElement(25, 2);
    grid.setElement(25, 6);
    grid.setElement(25, 7);
    grid.setElement(35, 3);
    grid.setElement(35, 4);
    grid.setElement(36, 3);
    grid.setElement(36, 4);
}
