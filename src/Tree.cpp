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

//copy constructor implementation
Tree::Tree(const Tree &oth): node(oth.node), children(){
for (Tree* p_child : oth.children){
    this->addChild(*p_child);
}
}
//copy assignment operator implementation
Tree &Tree::operator=(const Tree &oth) {
    if (&oth == this)
        return *this;
}

//move assignment operator implementation
Tree &Tree::operator=(Tree &&oth) {
    if (&oth == this)
        return *this;

}

//move constructor implementation
Tree::Tree(Tree &&oth) {

}

//destructor implementation
Tree::~Tree() {

}

CycleTree::CycleTree(int rootLabel, int currCycle): Tree(rootLabel), currCycle(currCycle){

}

int CycleTree::traceTree() {
    return 0;
}

CycleTree::CycleTree(const CycleTree &oth): Tree(oth), currCycle(oth.currCycle){

}

CycleTree *CycleTree::clone() const{
    return new CycleTree(*this);
}

MaxRankTree::MaxRankTree(int rootLabel) : Tree(rootLabel){

}

int MaxRankTree::traceTree() {
    return 0;
}

MaxRankTree *MaxRankTree::clone() const {
    return new MaxRankTree(*this);
}

RootTree::RootTree(int rootLabel) : Tree(rootLabel) {

}

int RootTree::traceTree() {
    return 0;
}

RootTree *RootTree::clone() const {
    return new RootTree(*this);
}
