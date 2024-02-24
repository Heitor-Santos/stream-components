#include "node.h"

#include <iostream>

using namespace std;

Node::Node(bool _occupied, int _element) {
    occupied = _occupied;
    rank = 0;
    parent = nullptr;
    element = _element;
    prev_sibling = nullptr;
    next_sibling = nullptr;
    prev_sibling_with_children = nullptr;
    next_sibling_with_children = nullptr;
    children_count = 0;
    children_with_children_count = 0;
    children_tail = nullptr;
    children_with_children_tail = nullptr;
}

bool Node::isLeaf(){
    return children_count == 0;
}

bool Node::isRoot(){
    return parent == nullptr;
}

bool Node::hasPrevChildren(){
    return prev_sibling != nullptr;
}

bool Node::hasPrevChildrenWithChildren(){
    return prev_sibling_with_children != nullptr;
}

bool Node::isTailofTheChildrenList(){
    return next_sibling == nullptr;
}

bool Node::isTailofTheChildrenWithChildrenList(){
    return next_sibling_with_children == nullptr;
}