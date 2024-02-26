#pragma once
#include "../../utils.h"

#include <unordered_map>
#include <set> 
#include <list>

class OriginalStreamer : public Streamer{

private:
    FileWriter writer;
    std::unordered_map<int, int> mapping_components;
    std::unordered_map<int, std::set<int>> component_members;

public:
    OriginalStreamer(std::string &output_file);
    bool update_components(int curr_read, const std::list<edge>& incoming_edges, const std::list<edge>& outgoing_edges, const std::set<int>& removed_nodes) override;
    std::string report_components() override;

private:
    void relabel_components(int curr_read, const bool incoming, const std::list<edge>& edge_list, const std::set<int>& removed_nodes);
};