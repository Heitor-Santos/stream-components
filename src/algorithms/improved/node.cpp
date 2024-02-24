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

bool Node::hasOnlyOneChild(){
    return children_count == 1;
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

void Node::removeFromParentChildren(){
    if(!isRoot()){
        if(hasPrevChildren()) prev_sibling->next_sibling = next_sibling;
        if(isTailofTheChildrenList()) parent->children_tail = prev_sibling;
        parent->children_count--;
        if(hasPrevChildrenWithChildren()) prev_sibling_with_children->next_sibling_with_children = next_sibling_with_children;
        if(isTailofTheChildrenWithChildrenList()) parent->children_with_children_tail = prev_sibling_with_children;
        parent->children_with_children_count--;
    }
}

void Node::addOnlyChildToParentChildren(){
    Node* only_child = children_tail;
    Node* parent_last_child = parent->children_tail;
    if(parent_last_child != nullptr){
        parent_last_child->next_sibling = only_child;
        only_child->prev_sibling = parent_last_child;
    }
    parent->children_tail = only_child;
    parent->children_count++;
}

void Node::addOnlyChildToParentChildrenWithChildren(){
    Node* only_child = children_tail;
    Node* parent_last_child_with_children = parent->children_with_children_tail;
    if(parent_last_child_with_children != nullptr){
        parent_last_child_with_children->next_sibling_with_children = only_child;
        only_child->prev_sibling_with_children = parent_last_child_with_children;
    }
    parent->children_with_children_tail = only_child;
    parent->children_with_children_count++;
}