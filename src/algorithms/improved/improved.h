#pragma once
#include "../../utils.h"
#include "union-find.h"

#include <unordered_map>
#include <set> 
#include <list>

class ImprovedStreamer : public Streamer{

private:
    FileWriter writer;
    UnionFind union_find;

public:
    ImprovedStreamer(std::string &output_file);
    std::string update_components(int curr_read, const std::list<edge>& incoming_edges, const std::list<edge>& outgoing_edges, const std::set<int>& removed_nodes) override;
private:
    void unionIncomingEdges(int curr_read, const std::list<edge>& incoming_edges);
    void unionOutgoingEdges(int curr_read, const std::list<edge>& outgoing_edges);
    void relabel_components(int curr_read, const bool incoming, const std::list<edge>& edge_list, const std::set<int>& removed_nodes);
};