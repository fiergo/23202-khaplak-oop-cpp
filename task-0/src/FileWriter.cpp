#include "FileWriter.h"

void FileWriter::open() {
    out->open(filename);
}

void FileWriter::close() {
    out->close();
    delete out;
}

void FileWriter::printString(const std::string& string) {
    *out << string;
}

FileWriter::FileWriter(const std::string& filename) {
    this->filename = filename;
    auto* out = new std::ofstream;
    this->out = out;
    FileWriter::open();
}