#include "gtest/gtest.h"
#include "../src/FileReader.h"
#include <fstream>
#include <sstream>

std::string createTempFile(const std::string& content) {
    std::ofstream tempFile;
    std::string tempFileName = "temp_file.txt";
    tempFile.open(tempFileName);
    tempFile << content;
    tempFile.close();
    return tempFileName;
}

void deleteTempFile(const std::string& tempFileName) {
    std::remove(tempFileName.c_str());
}


TEST(FileReaderTest, ReadSingleLine) {
    std::string fileContent = "This is a test line.";
    std::string tempFileName = createTempFile(fileContent);

    FileReader reader(tempFileName);
    std::string line = reader.getLine();

    ASSERT_EQ(line, fileContent);
    ASSERT_TRUE(reader.isNextEOF());

    deleteTempFile(tempFileName);
}



TEST(FileReaderTest, ReadMultipleLines) {
    std::string fileContent = "Line 1\nLine 2\nLine 3";
    std::string tempFileName = createTempFile(fileContent);

    FileReader reader(tempFileName);
    std::string line1 = reader.getLine();
    std::string line2 = reader.getLine();
    std::string line3 = reader.getLine();

    ASSERT_EQ(line1, "Line 1");
    ASSERT_EQ(line2, "Line 2");
    ASSERT_EQ(line3, "Line 3");
    ASSERT_TRUE(reader.isNextEOF());

    deleteTempFile(tempFileName);
}


TEST(FileReaderTest, EmptyFile) {
    std::string fileContent;
    std::string tempFileName = createTempFile(fileContent);

    FileReader reader(tempFileName);
    std::string line = reader.getLine();

    ASSERT_TRUE(line.empty());
    ASSERT_TRUE(reader.isNextEOF());

    deleteTempFile(tempFileName);
}


TEST(FileReaderTest, FileWithTrailingNewline) {
    std::string fileContent = "Test line\n";
    std::string tempFileName = createTempFile(fileContent);
    FileReader reader(tempFileName);
    std::string line = reader.getLine();

    ASSERT_EQ(line, "Test line");
    ASSERT_TRUE(reader.isNextEOF());
    deleteTempFile(tempFileName);
}


TEST(FileReaderTest, isNextEOF_False) {
    std::string fileContent = "Test Line";
    std::string tempFileName = createTempFile(fileContent);
    FileReader reader(tempFileName);

    ASSERT_FALSE(reader.isNextEOF());
    reader.getLine();
    ASSERT_TRUE(reader.isNextEOF());

    deleteTempFile(tempFileName);
}
