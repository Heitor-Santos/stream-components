#pragma once

class Node{

private:
    bool occupied;
    int rank;
    Node* parent;
    int element;
    Node* prev_sibling;
    Node* next_sibling;
    int children_count;
    Node* children_tail;

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
};