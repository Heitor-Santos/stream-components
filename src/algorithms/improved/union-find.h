#pragma once
#include "node.h"

#include <unordered_map>

class UnionFind{

private:
    std::unordered_map<int,Node*> uf;

private:
    Node* findAux(Node*);
    void unionAux(Node* parent, Node* node);
    
public:
    UnionFind();
    Node* find(int index);
    void makeset(int element);
    void unionElements(int indexA, int indexB);
    void deleteElement(int index);
};