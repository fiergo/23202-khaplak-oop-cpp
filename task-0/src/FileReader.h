#pragma once

#include <fstream>
#include <string>
#include <iostream>

class FileReader {
private:
    std::string filename;
    std::ifstream* in;
public:
    void open();
    void close();
    bool isNextEOF();
    std::string getLine();
    explicit FileReader(const std::string& filename);
};

