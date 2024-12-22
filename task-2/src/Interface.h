#pragma once
#include <iostream>
#include <string>
#include <vector>

class Cmd {
private:
    std::string name;
    std::string attributesString;
public:
    explicit Cmd(const std::string& cmd);
    std::string getName();
    std::string getAttributes();
};

class Interface {
private:
    void printGrid(const std::vector<std::vector<bool>>& grid);
public:
    void printInterface(const std::vector<std::vector<bool>>& grid, const std::vector<int>& birthCondition, const std::vector<int>& survivalCondition,
                        const std::string& universeName, int iterationNum, const bool* parseLifeFIleStatus);
    Cmd getCommand();
    void printHelp();
};