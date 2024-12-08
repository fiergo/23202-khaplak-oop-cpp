#pragma once

#include "FileReader.h"
#include "WordStatistics.h"

class FileWriter
{
private:
    std::string filename;
    std::ofstream* out;
public:
    void open();
    void close();
    void printString(const std::string& string);
    explicit FileWriter(const std::string& filename);
};