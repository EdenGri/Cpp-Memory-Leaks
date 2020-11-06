//
// Created by spl211 on 31/10/2020.
//

#include <Tree.h>

using namespace std;

Tree::Tree(int rootLabel): node(rootLabel), children(){

}

void Tree::addChild(const Tree &child) {
    vector<Tree*>& vec_old = this->children;
    Tree* item = child.clone();
    vector<Tree*> vec_new = vector<Tree*>(); // vector<Tree*> vec_new; calls empty
   if(vec_old.empty()){
       vec_old.push_back(item);
       return;
   }
    int i = 0;
    for(;vec_old[i]->node < item ->node; i++){
        if (vec_old[i]->node < item->node)
            vec_new.push_back((vec_old[i])); // we did push back to pointer and therefore dont need to delete old pointers and there is no memory leak
    }
    vec_new.push_back(item);
    for(; i < vec_old.size(); i++)
        vec_new.push_back(vec_old[i]);

    this->children = vec_new;
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
Tree &Tree::operator=(const Tree& oth) {
    if (this != &oth) {
        node = oth.node;
    }
    int i = 0;
    //clear existing children list
    for(; i < children.size(); i++)
        delete children[i];
    //Add new children list
    for(; i < oth.children.size(); i++){
        children.push_back(oth.children[i]);
    }
    return *this;
}

//move assignment operator implementation ****??
Tree &Tree::operator=(Tree &&oth) {
    if (&oth == this)
        return *this;

}

//move constructor implementation ***??
Tree::Tree(Tree &&oth) {

}

//destructor implementation
Tree::~Tree() {

}

int Tree::getNode() const { //getter to get node
    return this->node;
}

CycleTree::CycleTree(int rootLabel, int currCycle): Tree(rootLabel), currCycle(currCycle){

}

int CycleTree::traceTree() {
    return 0;
}


CycleTree *CycleTree::clone() const{
    return new CycleTree(*this);
}

MaxRankTree::MaxRankTree(int rootLabel) : Tree(rootLabel){

}

int MaxRankTree::traceTree() {
    int max_children = 0;
    vector<Tree*> =
    return 0;
}

MaxRankTree *MaxRankTree::clone() const {
    return new MaxRankTree(*this);
}

RootTree::RootTree(int rootLabel) : Tree(rootLabel) {

}

int RootTree::traceTree() {
    return getNode();
}

RootTree *RootTree::clone() const {
    return new RootTree(*this);
}
