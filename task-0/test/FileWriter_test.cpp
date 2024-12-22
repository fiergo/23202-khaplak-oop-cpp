#include "gtest/gtest.h"
#include "../src/FileWriter.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>

std::string readFileContent(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << " for reading." << std::endl;
        return "";
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

void deleteFile(const std::string& filename) {
    if (std::remove(filename.c_str()) != 0)
    {
        std::cerr << "Error deleting file: " << filename << std::endl;
    }
}


TEST(FileWriterTest, WriteSingleLine) {
    const std::string filename = "test_single_line.txt";
    FileWriter writer(filename);
    std::vector<std::string> strings = {"test1", "test2", "test3"};
    writer.printString(strings);

    std::string fileContent = readFileContent(filename);
    ASSERT_EQ(fileContent, "Word;Frequency;Frequency(%)\ntest1;test2;test3\n");
    deleteFile(filename);
}


TEST(FileWriterTest, WriteMultipleLines) {
    const std::string filename = "test_multiple_lines.txt";
    FileWriter writer(filename);
    std::vector<std::string> strings1 = {"data1","data2","data3"};
    writer.printString(strings1);
    std::vector<std::string> strings2 = {"data4", "data5", "data6"};
    writer.printString(strings2);
    std::vector<std::string> strings3 = {"data7","data8","data9"};
    writer.printString(strings3);

    std::string fileContent = readFileContent(filename);
    ASSERT_EQ(fileContent, "Word;Frequency;Frequency(%)\ndata1;data2;data3\ndata4;data5;data6\ndata7;data8;data9\n");
    deleteFile(filename);
}


TEST(FileWriterTest, EmptyString) {
    const std::string filename = "test_empty_string.txt";
    FileWriter writer(filename);
    std::vector<std::string> strings = {"", "", ""};
    writer.printString(strings);

    std::string fileContent = readFileContent(filename);
    ASSERT_EQ(fileContent, "Word;Frequency;Frequency(%)\n");
    deleteFile(filename);
}


TEST(FileWriterTest, FileCreation) {
    const std::string filename = "test_creation.txt";
    {
        FileWriter writer(filename);
    }
    std::ifstream file(filename);
    ASSERT_TRUE(file.good());
    deleteFile(filename);
}


TEST(FileWriterTest, CorrectHeader) {
    const std::string filename = "test_correct_header.txt";
    FileWriter writer(filename);
    std::string fileContent = readFileContent(filename);

    ASSERT_EQ(fileContent, "Word;Frequency;Frequency(%)");
    deleteFile(filename);
}
