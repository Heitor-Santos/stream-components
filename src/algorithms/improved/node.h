#pragma once
#include <set>

class Node{

private:
    bool occupied;
    int rank;
    Node* parent;
    int element;
    int orig_element;
    Node* prev_sibling;
    Node* next_sibling;
    int children_count;
    Node* children_tail;
    int minChild;
    std::set<int>children_values;

private:
    void addNodeToParentChildren(Node* node);

public:
    Node(bool occupied, int element);
    bool isLeaf();
    bool isRoot();
    bool hasPrevChildren();
    bool hasOnlyOneChild();
    bool isTailofTheChildrenList();
    void removeFromParentChildren();
    void addToParentChildren();
    void addOnlyChildToParentChildren();
    Node* getParent();
    Node* setParent(Node* _parent);
    int getRank();
    Node* setRank(int _rank);
    bool isOccupied();
    Node* setOccupied(bool _occupied);
    Node* onlyChild();
    int getElement();
    Node* setElement(int _element);
    Node* updateElementToMinChild();
    Node* resetElement();
    Node* minNode();
};