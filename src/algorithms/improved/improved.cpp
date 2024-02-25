#include "improved.h"

#include <iostream>

using namespace std;


ImprovedStreamer::ImprovedStreamer(string &output_file) {
    writer = FileWriter(output_file);
    union_find = UnionFind();
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

string ImprovedStreamer::update_components(int curr_read, const list<edge>& incoming_edges, const list<edge>& outgoing_edges, const set<int>& removed_nodes) {
  if (removed_nodes.find(curr_read) != removed_nodes.end()) {
    return "empty";
  } 
  
  // The current read starts off as its own component 
  union_find.makeset(curr_read);

  unionIncomingEdges(curr_read, incoming_edges);
  unionOutgoingEdges(curr_read, outgoing_edges);


  // Updates nodes affected by transitive closures
  for(int removed_node : removed_nodes) {
    union_find.deleteElement(removed_node); 
  }
  //Utils().printOrderedMap(union_find.getComponents());
  string text = Utils().orderedMapText(union_find.getComponents());
  writer.append_text(text);
  return text;
}
