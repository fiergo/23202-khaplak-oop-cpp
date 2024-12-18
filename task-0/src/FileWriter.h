#pragma once

#include "FileReader.h"
#include "vector"

class FileWriter
{
private:
    std::string filename;
    std::ofstream* out;
public:
    void open();
    void close();
    void printString(const std::vector<std::string>& strings);
    explicit FileWriter(const std::string& filename);
};