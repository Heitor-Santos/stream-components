#include "improved.h"

#include <iostream>

using namespace std;


ImprovedStreamer::ImprovedStreamer(string &output_file) {
    writer = FileWriter(output_file);
    union_find = UnionFind();
    temp_node_counter = -1;
}

void ImprovedStreamer::unionIncomingEdges(int curr_read, const list<edge>& incoming_edges){
    for(edge e: incoming_edges){
        union_find.unionElements(e.source, curr_read);
    }
}

void ImprovedStreamer::unionOutgoingEdges(int curr_read, const list<edge>& outgoing_edges){
    for(edge e: outgoing_edges){
        union_find.unionElements(e.target, curr_read);
    }
}

bool ImprovedStreamer::update_components(int curr_read, const list<edge>& incoming_edges, const list<edge>& outgoing_edges, const set<int>& removed_nodes) {
  if (removed_nodes.find(curr_read) != removed_nodes.end()) {
    return false;
  } 
  //cout<<"improved "<<curr_read<<endl;
  
  // The current read starts off as its own component 
  union_find.makeset(curr_read);

  unionIncomingEdges(curr_read, incoming_edges);
  unionOutgoingEdges(curr_read, outgoing_edges);

  int aux_counter=temp_node_counter;
  
  for(int removed_node : removed_nodes) {
    //Utils().printOrderedMap(union_find.getComponents());
    // if(union_find.findSmallest(removed_node)->getElement() == removed_node){
    //   union_find.unionElements(removed_node, curr_read);
    // } 
    union_find.unionElements(removed_node, curr_read);
    union_find.deleteElement(removed_node); 
    temp_node_counter--;
  }
  
  //cout<<"oxe"<<endl;
  return true;
  //Utils().printOrderedMap(union_find.getComponents());
  
}

string ImprovedStreamer::report_components(){
  string text = Utils().orderedMapText(union_find.getComponents());
  writer.append_text(text);
  return text;
}