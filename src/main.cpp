#include "utils.h"
#include "algorithms/original/original.h"
#include "algorithms/improved/improved.h"

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

void printEdge(edge e){
    cout<<e.source <<" "<< e.target <<" "<< e.slength 
    <<" "<< e.tlength <<" "<< e.overlap <<" "<< e.sorient <<" "<< e.torient<<endl;
}

void printDifferences(int curr_read, set<int>&removed_nodes, 
    list<edge>&incoming_edges, list<edge>&outgoing_edges, string& original, string& improved){
    cout<<curr_read<<endl;
    for(auto node: removed_nodes)cout<<node<<" ";
    cout<<"\n";
    for(auto in_edge: incoming_edges)printEdge(in_edge);
    for(auto out_edge: outgoing_edges)printEdge(out_edge);
    cout<<"-----------------------------------------------------"<<endl;
    cout<<original<<endl;
    cout<<"-----------------------------------------------------"<<endl;
    cout<<improved<<endl;
}

int main(int argc, char **argv) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string algorithm(argv[1]);
    string input_file(argv[2]);
    string output_file(argc > 3 ? argv[3]:"output");
    FileReader reader(input_file, false);
    int curr_read;
    set<int>removed_nodes;
    list<edge>incoming_edges;
    list<edge>outgoing_edges;
    string output_file_original = output_file+"_original";
    string output_file_improved = output_file+"_improved";
    OriginalStreamer originalStreamer(output_file_original);
    ImprovedStreamer improvedStreamer(output_file_improved);
    string line, original, improved;
    Streamer* streamerPtr;
    bool fullReport = algorithm[0]=='f';
    if (algorithm == "original" || algorithm == "foriginal") {
        streamerPtr = &originalStreamer;
    } else {
        streamerPtr = &improvedStreamer;
    }
    while (reader.next_line(line)) {
        curr_read = stoi(line);
        removed_nodes = processSet(reader);
        incoming_edges = processEdges(reader);
        outgoing_edges = processEdges(reader);
        if(algorithm=="debug"){
            bool updatedOriginal =  originalStreamer.update_components(curr_read, incoming_edges, outgoing_edges, removed_nodes);
            bool updatedImproved = improvedStreamer.update_components(curr_read, incoming_edges, outgoing_edges, removed_nodes);
            original = updatedOriginal ? originalStreamer.report_components() : "empty";
            improved = updatedImproved ? improvedStreamer.report_components() : "empty";
            if(original != improved){
                printDifferences(curr_read, removed_nodes, incoming_edges, outgoing_edges, original, improved);
                break;
            }
        }
        else{
            bool updated = streamerPtr->update_components(curr_read, incoming_edges, outgoing_edges, removed_nodes);
            if(fullReport && updated)streamerPtr->report_components();
        }
    }
    if(!fullReport)streamerPtr->report_components();
    reader.close();
}