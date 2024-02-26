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

void UnionFind::deleteElement(int index){
    Node* node = uf[index];
    node->setOccupied(false);
    if(!node->isLeaf()){
        //faz sentido essa condição do isroot?
        //depois tentar remover todos children with children
        if(node->hasOnlyOneChild()){
            node->onlyChild()->setParent(node->getParent());
            node->removeFromParentChildren();
            node->addOnlyChildToParentChildren();
        }
    }

    else{
        //tem q deletar node tbm
        node->removeFromParentChildren();
        Node* parent = node->getParent();
        if(!node->isRoot() && parent->isLeaf()) parent->setRank(0);
        if(!node->isRoot() && !parent->isOccupied() && parent->hasOnlyOneChild()){
            parent->onlyChild()->setParent(parent->getParent());
            parent->removeFromParentChildren();
            parent->addOnlyChildToParentChildren();
        }
    }
    uf[index] = nullptr;
}

unordered_map<int, set<int>> UnionFind::getComponents(){
    unordered_map<int, set<int>> components = unordered_map<int, set<int>>();
    for (const auto& pair : uf) {
        if(pair.second != nullptr){
            int root = find(pair.first)->getElement();
            if (components.find(root) == components.end()) {
                components[root] = set<int>(); // Inicializa o conjunto se a chave não existir
            }
            components[root].insert(pair.first);
        }
    }
    return components;
}