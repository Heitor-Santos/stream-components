#include "node.h"
#include <iostream>
#include <limits.h>

using namespace std;

Node::Node(bool _occupied, int _element) {
    occupied = _occupied;
    rank = 0;
    parent = nullptr;
    element = _element;
    prev_sibling = nullptr;
    next_sibling = nullptr;
    children_count = 0;
    children_tail = nullptr;
    minChild = __INT_MAX__;
    children_values = set<int>();
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

bool Node::isTailofTheChildrenList(){
    return next_sibling == nullptr;
}

void Node::removeFromParentChildren(){
    if(!isRoot()){
        if(hasPrevChildren()) prev_sibling->next_sibling = next_sibling;
        if(isTailofTheChildrenList()) parent->children_tail = prev_sibling;
        parent->children_count--;
        parent->children_values.erase(element);
        //cout<<"removed né"<<endl;
    // for (auto it = parent->children_values.begin(); it != parent->children_values.end(); ++it)
    //     cout << ' ' << *it;
    // cout<<endl;
    }
}

void Node::addNodeToParentChildren(Node* node){
    if(!isRoot()){
        parent->children_values.insert(node->element);
        // cout<< node->element<<endl;
        // cout<<"added né"<<endl;
        // for (auto it = parent->children_values.begin(); it != parent->children_values.end(); ++it)
        //     cout << ' ' << *it;
        // cout<<endl;
        Node* parent_last_child = parent->children_tail;
        if(parent_last_child != nullptr){
           parent_last_child->next_sibling = node;
           node->prev_sibling = parent_last_child;
        }
        parent->children_tail = node;
        parent->children_count++;   
    }
    else{
        node->prev_sibling = nullptr;
        node->next_sibling = nullptr;
    }
}

void Node::addToParentChildren(){
    addNodeToParentChildren(this);
}

void Node::addOnlyChildToParentChildren(){
    addNodeToParentChildren(children_tail);
}

Node* Node::getParent(){
    return parent;
}

Node* Node::setParent(Node* _parent){
    parent = _parent;
    return this;
}

int Node::getRank(){
    return rank;
}

Node* Node::setRank(int _rank){
    rank = _rank;
    return this;
}

bool Node::isOccupied(){
    return occupied;
}

Node* Node::setOccupied(bool _occupied){
    occupied = _occupied;
    return this;
}

Node* Node::onlyChild(){
    return children_tail;
}

int Node::getElement(){
    return element;
}

Node* Node::setElement(int _element){
    element = _element;
    return this;
}

Node* Node::updateElementToMinChild(){
    auto it = children_values.begin();
    int min_child = *it;
    element = min_child;
    //cout<<"updated né"<<endl;
    children_values.erase(min_child);
    // for (auto it = children_values.begin(); it != children_values.end(); ++it)
    //     cout << ' ' << *it;
    // cout<<endl;

    return this;
}

Node* Node::resetElement(){
    element = orig_element;
    return this;
}

Node* Node::minNode() {
    Node* min_node = this;
    cout<<element<<" "<<occupied<<" "<<(parent == nullptr? -1 : parent->element)<<endl;
    if (children_tail == nullptr) {
        return min_node;
    }


    // Recursivamente chama getAllNodes() para cada nó filho
    int min = isOccupied()? element : INT_MAX;
    Node* child = children_tail;
    while (child != nullptr) {
        cout<<child->getElement()<<" ---:"<<endl;
        Node* child_min = child->minNode();
        if(child_min->getElement()<min&&child_min->isOccupied()){
            min_node=child_min;
            min=child_min->getElement();
        }
        child = child->prev_sibling;
        cout<<min_node->getElement()<<" ooo"<<endl;
    }
    cout<<min_node->getElement()<<endl;
    return min_node;
}