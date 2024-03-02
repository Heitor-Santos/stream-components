#include "union-find.h"
#include <iostream>

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

Node* UnionFind::findSmallest(int element){
    Node* root = find(element);
    cout<<"a root é :"<<root->getElement()<<endl;
    return root->minNode();
}

void UnionFind::makeset(int element){
    Node* node = new Node(true, element);
    uf[element] = node;
}

void UnionFind::unionAux(Node* parent, Node* node){
    //cout<<"nos a unir "<<parent->getElement()<<" "<<node->getElement()<<endl;
    Node* tempParent = node->getParent();
    // cout<<"oldParent "<<(tempParent == nullptr ? INT16_MIN : tempParent->getElement())<<endl;
    // cout<<"new Parent is occupied "<<parent->isOccupied()<<endl;
    node->removeFromParentChildren();
    node->setParent(parent);
    node->addToParentChildren();
    int tail = INT16_MIN;
    if(tempParent!=nullptr && !tempParent->isLeaf())tail=tempParent->onlyChild()->getElement();
    // cout<<"oldParent tail "<<tail<<endl;
    // cout<<node->getParent()->getElement()<<endl;
    // cout<<node->getElement()<<" is leaf "<<node->isLeaf()<<endl;
    // if(!node->isLeaf())cout<<"leaf aí "<<node->onlyChild()->getElement()<<endl;
    // cout<<parent->getElement()<<" parent is leaf "<<parent->isLeaf()<<" "<<parent->isOccupied()<<endl;
    // if(!parent->isLeaf())cout<<"leaf aí "<<parent->onlyChild()->getElement()<<endl;
    // if(!parent->isRoot())cout<<parent->getParent()<<endl;
}

void UnionFind::unionElements(int indexA, int indexB){
    Node* rootA = find(indexA);
    Node* rootB = find(indexB);
    
    if (rootA == rootB) return; // Já estão no mesmo conjunto

    if (rootA->getRank() < rootB->getRank()) {
        std::swap(rootA, rootB); // Garante que rootA tenha a maior altura
    }

    int elRootA = rootA->getElement();
    int elRootB = rootB->getElement();

    // cout<<"n é possivel antes "<<endl;
    // cout<<rootA->getElement()<<" "<<rootA->isOccupied()<<endl;
    // cout<<rootB->getElement()<<" "<<rootB->isOccupied()<<endl;
    // if(elRootA>elRootB){
    //     rootA->setElement(elRootB);
    //     rootB->setElement(elRootA);
    //     rootA->setOccupied(rootB->isOccupied());
    //     rootB->setOccupied(rootA->isOccupied());
    // }
    // cout<<"n é possivel dps "<<endl;
    // cout<<rootA->getElement()<<" "<<rootA->isOccupied()<<endl;
    // cout<<rootB->getElement()<<" "<<rootB->isOccupied()<<endl;
    // uf[rootA->getElement()] = rootA;
    // uf[rootB->getElement()] = rootB;
    // cout<<elRootA<<" ufel "<<uf[elRootA]->getElement()<<endl;
    // cout<<elRootB<<" ufel "<<uf[elRootB]->getElement()<<endl;
    unionAux(rootA, rootB);

    if (rootA->getRank() == rootB->getRank()) {
        rootA->setRank(rootA->getRank() + 1); // Incrementa a altura de rootA
    }
}

void UnionFind::deleteElement(int index){
    Node* node = uf[index];
    node->setOccupied(false);
    uf[index]=nullptr;
    cout<<"a deletar "<<index<<endl;
    cout<<"a deletar real "<<node->getElement()<<endl;
    if(!node->isLeaf()){
    //    cout<<"não é leaf "<<" "<<node->onlyChild()->getElement()<<endl;
        //faz sentido essa condição do isroot?
        //depois tentar remover todos children with children
        if(node->hasOnlyOneChild()){
            node->onlyChild()->setParent(node->getParent());
            node->removeFromParentChildren();
            node->addOnlyChildToParentChildren();
            //node->resetElement();
        }
        //else node->updateElementToMinChild();
      //  cout<<"novo pai ein "<<node->getElement()<<endl;
    }

    else{
        // cout<<"é leaf"<<endl;
        // //tem q deletar node tbm
        node->removeFromParentChildren();
        Node* parent = node->getParent();
        if(!node->isRoot() && parent->isLeaf()) {
            parent->setRank(0);
            //parent->resetElement();
        }
        if(!node->isRoot() && !parent->isOccupied()){
            if(parent->hasOnlyOneChild()){
                parent->onlyChild()->setParent(parent->getParent());
                parent->removeFromParentChildren();
                parent->addOnlyChildToParentChildren();
            }
            //else parent->updateElementToMinChild();
        }
    }
}

bool UnionFind::isSingleSet(int index){
    Node* node = uf[index];
    return node !=nullptr && !node->isLeaf(); 
}

unordered_map<int, set<int>> UnionFind::getComponents(){
    unordered_map<int, set<int>> components = unordered_map<int, set<int>>();
    for (const auto& pair : uf) {
        if(pair.second != nullptr){
            Node* nodeRoot = find(pair.first); 
            int root = nodeRoot->getElement();
            cout<<pair.first<<" "<<pair.second->getElement()<<" "<<pair.second->isOccupied()<<endl;
            //cout<<"oooooooo "<<pair.first<<" "<<root<<endl;
            if (components.find(root) == components.end()) {
                components[root] = set<int>(); // Inicializa o conjunto se a chave não existir
            }
            components[root].insert(pair.first);
        }
    }
    return components;
}