//
// Created by spl211 on 31/10/2020.
//

#include <Tree.h>

using namespace std;

Tree::Tree(int rootLabel): node(rootLabel), children(){

}

void Tree::addChild(const Tree &child) {
this->children.push_back(child.clone());

}

Tree *Tree::createTree(const Session &session, int rootLabel) {
    return nullptr;
}

Tree::Tree(const Tree &oth): node(oth.node), children(){
for (Tree* p_child : oth.children){
    this->addChild(*p_child);
}
}

CycleTree::CycleTree(int rootLabel, int currCycle): Tree(rootLabel), currCycle(currCycle){

}

int CycleTree::traceTree() {
    return 0;
}

CycleTree::CycleTree(const CycleTree &oth): Tree(oth), currCycle(oth.currCycle){

}

CycleTree *CycleTree::clone() {
    return new CycleTree(*this);
}

MaxRankTree::MaxRankTree(int rootLabel) : Tree(rootLabel){

}

int MaxRankTree::traceTree() {
    return 0;
}

MaxRankTree *MaxRankTree::clone() {
    return new MaxRankTree(*this);
}

RootTree::RootTree(int rootLabel) : Tree(rootLabel) {

}

int RootTree::traceTree() {
    return 0;
}

RootTree *RootTree::clone() {
    return new RootTree(*this);
}
