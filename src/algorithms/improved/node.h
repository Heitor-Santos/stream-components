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

private:
    void addNodeToParentChildren(Node* node);
    void addNodeToParentChildrenWithChildren(Node* node);

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
    void addToParentChildren();
    void addToParentChildrenWithChildren();
    void addOnlyChildToParentChildren();
    void addOnlyChildToParentChildrenWithChildren();
    Node* getParent();
    Node* setParent(Node* _parent);
    int getRank();
    Node* setRank(int _rank);
    bool isOccupied();
    Node* setOccupied(bool _occupied);
    Node* onlyChild();
};