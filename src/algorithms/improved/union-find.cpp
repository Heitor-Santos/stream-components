#include "union-find.h"

using namespace std;


UnionFind::UnionFind(){
    uf = unordered_map<int,Node*>();
}

Node* UnionFind::findAux(Node* node){
    if(node->isRoot()) return node;
    return findAux(node->getParent());
}

Node* UnionFind::find(int element){
    return findAux(uf[element]);
}

void UnionFind::makeset(int element){
    Node* node = new Node(true, element);
    uf[element] = node;
}

void UnionFind::unionAux(Node* parent, Node* node){
    node->removeFromParentChildren();
    node->setParent(parent);
    node->addToParentChildren();
    if(!node->isLeaf())node->addToParentChildrenWithChildren();
}

void UnionFind::unionElements(int indexA, int indexB){
    Node* rootA = find(indexA);
    Node* rootB = find(indexB);
    if (rootA == rootB) return; // Já estão no mesmo conjunto

    if (rootA->getRank() < rootB->getRank()) {
        std::swap(rootA, rootB); // Garante que rootA tenha a maior altura
    }

    unionAux(rootA, rootB);

    if (rootA->getRank() == rootB->getRank()) {
        rootA->setRank(rootA->getRank() + 1); // Incrementa a altura de rootA
    }
}

void UnionFind::deleteElements(int index){
    Node* node = uf[index];
    node->setOccupied(false);
    if(!node->isLeaf()){
        if(!node->isRoot() && node->hasOnlyOneChild()){
            node->onlyChild()->setParent(node->getParent());
            node->removeFromParentChildren();
            node->addOnlyChildToParentChildren();
            if(!node->onlyChild()->isLeaf()){
                node->addOnlyChildToParentChildrenWithChildren();
            }
            uf[index] = nullptr;
        }
    }

    else{
        node->removeFromParentChildren();
        Node* parent = node->getParent();
        uf[index] = nullptr;
        if(!node->isRoot() && parent->isLeaf()) parent->setRank(0);
        if(!node->isRoot() && !parent->isOccupied() && parent->hasOnlyOneChild()){
            parent->onlyChild()->setParent(parent->getParent());
            parent->removeFromParentChildren();
            if(!parent->isRoot()){
                parent->addOnlyChildToParentChildren();
                if(!parent->onlyChild()->isLeaf()){
                    parent->addOnlyChildToParentChildrenWithChildren();
                }
            }
        }
    }
}