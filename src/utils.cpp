#include "utils.h"
#include <iostream>

using namespace std;

FileReader::FileReader(string filename, bool binary) {
    closed = false;
    if (!binary) file.open(filename);
    else file.open(filename, ifstream::binary);
}

bool FileReader::next_line(string &line) {
    if (getline(file, line)) {
        return true;
    }

    if (!closed) {
        file.close();
        closed = true;
    }

    return false;
}

void FileReader::close() {
    file.close();
}

FileWriter::FileWriter() {}

FileWriter::FileWriter(string &filename) {
    file.open(filename, ios_base::out | ios_base::binary);
}

void FileWriter::close() {
    file.close();
}

void FileWriter::append_text(string &text) {
    file.write(&text[0], (int) text.size());
}

Streamer::Streamer() {}