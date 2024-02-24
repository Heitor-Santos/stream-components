#include "utils.h"
#include "algorithms/original/original.h"

#include <iostream>
#include <string>
#include <iostream>
#include <queue>  
#include <vector> 
#include <unordered_map>
#include <stack> 
#include <set> 
#include <algorithm>
#include <list>
#include <boost/program_options.hpp>
using namespace std;
namespace po = boost::program_options;


edge createEdgeFromLine(const string& line) {
    edge e;
    istringstream iss(line);
    iss >> e.source >> e.target >> e.slength >> e.tlength >> e.overlap >> e.sorient >> e.torient;
    return e;
}

list<edge> processEdges(FileReader& reader) {
    string line;
    list<edge>edges;
    while (reader.next_line(line)) {
        if (line == "edges_end") {
            return edges; 
        }
        edges.push_back(createEdgeFromLine(line));
    }
    return edges;
}

set<int> createSetFromLine(const string& line) {
    set<int> intSet;
    istringstream iss(line);
    int num;
    while (iss >> num) {
        intSet.insert(num);
    }
    return intSet;
}

set<int> processSet(FileReader& reader) {
    string line;
    reader.next_line(line);
    return createSetFromLine(line);
}

int main(int argc, char **argv) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string algorithm(argv[1]);
    string input_file(argv[2]);
    string output_file(argc > 3 ? argv[3]:"output.txt");
    FileReader reader(input_file, false);
    string line;
    int curr_read;
    set<int>removed_nodes;
    list<edge>incoming_edges;
    list<edge>outgoing_edges;
    OriginalStreamer originalStreamer(output_file);
    Streamer& streamer = originalStreamer;
    while (reader.next_line(line)) {
        curr_read = stoi(line);
        removed_nodes = processSet(reader);
        incoming_edges = processEdges(reader);
        outgoing_edges = processEdges(reader);
        streamer.update_components(curr_read, incoming_edges, outgoing_edges, removed_nodes);
    }
    reader.close();
}