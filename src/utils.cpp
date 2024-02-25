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

Utils::Utils(){}

void Utils::printOrderedMap(const unordered_map<int, set<int>>& map) {
    // Criar um vetor para armazenar as chaves do mapa
    vector<int> sortedKeys;
    for (const auto& pair : map) {
        sortedKeys.push_back(pair.first);
    }

    // Ordenar as chaves do vetor
    sort(sortedKeys.begin(), sortedKeys.end());

    // Imprimir o mapa com índices e valores ordenados
    for (int key : sortedKeys) {
        for (int value : map.at(key)) {
          cout << value<< " ";
        }
        cout << endl;
    }
}

string Utils::orderedMapText(const unordered_map<int, set<int>>& map) {
    // Criar um vetor para armazenar as chaves do mapa
    vector<int> sortedKeys;
    for (const auto& pair : map) {
        sortedKeys.push_back(pair.first);
    }

    // Ordenar as chaves do vetor
    sort(sortedKeys.begin(), sortedKeys.end());

    // Imprimir o mapa com índices e valores ordenados
    string text="";
    for (int key : sortedKeys) {
        for (int value : map.at(key)) {
          text += to_string(value);
          text += " ";
        }
        text+="\n";
    }
    return text;
}