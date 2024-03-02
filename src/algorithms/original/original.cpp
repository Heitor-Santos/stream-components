#include "original.h"

#include <iostream>

using namespace std;

OriginalStreamer::OriginalStreamer(string &output_file) {
    writer = FileWriter(output_file);
    mapping_components = unordered_map<int, int>();
    component_members = unordered_map<int, set<int>>();
}

void OriginalStreamer::relabel_components(int curr_read, const bool incoming, const std::list<edge>& edge_list, const std::set<int>& removed_nodes) {

  // Find the minimum root id
  int min_root = mapping_components[curr_read]; 
  for(edge e : edge_list) {
    int neighbor = e.source; 
    if (!incoming) neighbor = e.target;
    int neighbor_root = mapping_components[neighbor];
    if (removed_nodes.find(neighbor_root) != removed_nodes.end()) continue;  
    if (neighbor_root < min_root) min_root = neighbor_root;
  }

  // Handle the current read 
  component_members[min_root].insert(curr_read);
  if(min_root != mapping_components[curr_read]) {
    int prev_root = mapping_components[curr_read];
    for(int member : component_members[prev_root]) {
      mapping_components[member] = min_root;
      component_members[min_root].insert(member);
    }
    component_members.erase(prev_root);
  }
  
  // Handle all of the current read's neighbors 
  for(edge e : edge_list) {
    int neighbor = e.source; 
    if (!incoming) neighbor = e.target; 
    if (mapping_components[neighbor] == min_root) continue; 
    int prev_root = mapping_components[neighbor];
    for(int member : component_members[prev_root]) {
      mapping_components[member] = min_root;
      component_members[min_root].insert(member);
    }
    component_members.erase(prev_root);
  }
}

bool OriginalStreamer::update_components(int curr_read, const std::list<edge>& incoming_edges, const std::list<edge>& outgoing_edges, const std::set<int>& removed_nodes) {
  if (removed_nodes.find(curr_read) != removed_nodes.end()) {
    return false;
  } 
  // cout<<"original"<<endl;
  // Utils().printOrderedMap(component_members);
  // cout<<"ALLLLLOOOOOO1"<<endl;
  // cout<<mapping_components[74]<<" "<<mapping_components[75]<<endl;
  // The current read starts off as its own component 
  mapping_components[curr_read] = curr_read; 
  component_members[curr_read] = std::set<int>(); 
  component_members[curr_read].insert(curr_read);

  relabel_components(curr_read, true, incoming_edges, removed_nodes);
  relabel_components(curr_read, false, outgoing_edges, removed_nodes);
  // cout<<"original"<<endl;
  // Utils().printOrderedMap(component_members);
  //cout<<"ALLLLLOOOOOO2"<<endl;
  // cout<<mapping_components[74]<<" "<<mapping_components[75]<<endl;
  // Updates nodes affected by transitive closures
  //Utils().printOrderedMap(component_members);
  //cout<<"ooohhhh "<<curr_read<<endl;
  for(int removed_node : removed_nodes) {
    int root_of_removed_node = mapping_components[removed_node]; 
    //cout<<" "<<root_of_removed_node<<" roor"<<endl;
    //Utils().printOrderedMap(component_members);
    //cout<<"pppppppppppppp"<<endl;
    if (component_members.find(root_of_removed_node) != component_members.end()) {
      component_members[root_of_removed_node].erase(removed_node);
    }
    //Utils().printOrderedMap(component_members);
    //cout<<"14444444"<<endl;
    //cout<<mapping_components[14]<<endl;
    // for(auto k: component_members[14])cout<<k;
    // cout<<"\n";
    // cout<<"9444444"<<endl;
    // cout<<mapping_components[94]<<endl;
    // for(auto k: component_members[94])cout<<k;
    // cout<<"\naaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\n";
    // // cout<<"ALLLLLOOOOOO3"<<endl;
    // cout<<mapping_components[74]<<" "<<mapping_components[75]<<endl;
    // cout<<"MENOR ORIG "<<removed_node<<endl;
    // Utils().printOrderedMap(component_members);
    if (component_members.find(root_of_removed_node) != component_members.end()) {
      if(root_of_removed_node != mapping_components[curr_read]){
        for (auto removed_node_member : component_members[root_of_removed_node]) {
          if (removed_nodes.find(removed_node_member) == removed_nodes.end()) {
            component_members[mapping_components[curr_read]].insert(removed_node_member);
            mapping_components[removed_node_member] = mapping_components[curr_read];
          }
        }
        component_members.erase(root_of_removed_node);
      }
      component_members.erase(removed_node);
    }
    
    // cout<<"ALLLLLOOOOOO4"<<endl;
    // cout<<mapping_components[74]<<" "<<mapping_components[75]<<endl;
    // cout<<"maps"<<endl;
    // for(auto& pair: mapping_components)cout<<pair.first<<" "<<pair.second<<endl;
    mapping_components.erase(removed_node); 
    
    // cout<<"ALLLLLOOOOOO5"<<endl;
    // for(auto& pair: mapping_components)cout<<pair.first<<" "<<pair.second<<endl;
    // cout<<"maps finish"<<endl;
    // cout<<removed_node<<endl;
    // cout<<mapping_components[74]<<" "<<mapping_components[75]<<endl;
  }
  
  return true;
  
  //Utils().printOrderedMap(component_members);
  //printValues(mapping_components, component_members);
}

string OriginalStreamer::report_components(){
  //cout<<mapping_components[74]<<" "<<mapping_components[75]<<endl;
  string compText = Utils().orderedMapText(component_members);
  writer.append_text(compText);
  return compText;
}