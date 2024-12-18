#include "FileWriter.h"

void FileWriter::open() {
    out->open(filename);
}

void FileWriter::close() {
    out->close();
    delete out;
}

void FileWriter::printString(const std::vector<std::string>& strings) {
    *out << strings[0] << ";" << strings[1] << ";" << strings[2] << std::endl;
}

FileWriter::FileWriter(const std::string& filename) {
    this->filename = filename;
    auto* out = new std::ofstream;
    this->out = out;
    FileWriter::open();
}

void FilePrinter::printInt(int n) {
    *out << n;
}