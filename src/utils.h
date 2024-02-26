#pragma once
#include <fstream>
#include <string>
#include <string.h>
#include <list>
#include <set> 
#include <vector>
#include <unordered_map>
#include <algorithm>

struct edge {
    int source;
    int target;
    int slength;
    int tlength;
    int overlap;
    char sorient;
    char torient;
};

class FileReader {
private:
    bool closed;
    std::ifstream file;

public:
    FileReader(std::string filename, bool binary);

    bool next_line(std::string &line);
    void close();
};

class FileWriter {
private:
    std::ofstream file;

public:
    FileWriter();
    FileWriter(std::string &filename);

    void close();
    void append_text(std::string &text);
};

class Streamer {
public:
    Streamer();
    virtual bool update_components(int curr_read, const std::list<edge>& incoming_edges, const std::list<edge>& outgoing_edges, const std::set<int>& removed_nodes)=0;
    virtual std::string report_components()=0;
};

class Utils{
public:
    Utils();
    void printOrderedMap(const std::unordered_map<int, std::set<int>>& map);
    std::string orderedMapText(const std::unordered_map<int, std::set<int>>& map);
};