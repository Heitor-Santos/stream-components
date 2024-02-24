#pragma once

class Node{

private:
    bool occupied;
    int rank;
    Node* parent;
    int element;
    Node* prev_sibling;
    Node* next_sibling;
    Node* prev_sibling_with_children;
    Node* next_sibling_with_children;
    int children_count;
    int children_with_children_count;
    Node* children_tail;
    Node* children_with_children_tail;

public:
    Node(bool occupied, int element);
    bool isLeaf();
    bool isRoot();
    bool hasPrevChildren();
    bool hasOnlyOneChild();
    bool hasPrevChildrenWithChildren();
    bool isTailofTheChildrenList();
    bool isTailofTheChildrenWithChildrenList();
    void removeFromParentChildren();
    void addOnlyChildToParentChildren();
    void addOnlyChildToParentChildrenWithChildren();
};