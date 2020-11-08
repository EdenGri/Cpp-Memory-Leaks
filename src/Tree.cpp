//
// Created by spl211 on 31/10/2020.
//

#include <Tree.h>
#include <iostream>

#include "Session.h"

using namespace std;

Tree::Tree(int rootLabel) : node(rootLabel), children() {
}

void Tree::addChild(const Tree &child) {
    vector<Tree *> &vec_old = this->children; //easier todo delete
    Tree *item = child.clone();
    vector<Tree *> vec_new = vector<Tree *>(); // vector<Tree*> vec_new; calls empty constructor todo
    if (vec_old.empty()) {
        vec_old.push_back(item);
        return;
    }
    int i = 0;
    for (; vec_old[i]->node < item->node; i++) {
        if (vec_old[i]->node < item->node)
            vec_new.push_back((vec_old[i])); // we did push back to pointer and therefore dont need to delete old pointers and there is no memory leak todo delete
    }
    vec_new.push_back(item);
    for (; i < vec_old.size(); i++)
        vec_new.push_back(vec_old[i]);

    this->children = vec_new;
}

Tree *Tree::createTree(const Session &session, int rootLabel) { //todo
    return nullptr;
}

//copy constructor implementation
Tree::Tree(const Tree &oth) : node(oth.node), children() {
    for (Tree *p_child : oth.children) {
        this->addChild(*p_child);
    }
}

//copy assignment operator implementation
Tree &Tree::operator=(const Tree &oth) {
    if (this == &oth)
        return *this;

    this->node = oth.node; //updates node field todo delete

    //clear existing children list
    //we can press on highlighted for and make prettier for todo delete
    for (int i = 0; i < children.size(); i++) //deletes pointers in me vector
        delete children[i];

    children.clear(); //clears vector and makes it size 0

    //Add new children list from other vector
    for (int i = 0; i < oth.children.size(); i++)
        children.push_back(oth.children[i]->clone()); //creates copy with diff location on heap using clone (deep-copy) todo delete

    return *this;
}

//move assignment operator implementation
Tree &Tree::operator=(Tree &&oth) {
    if (&oth == this)
        return *this;

    this->node = oth.node;

    //swap is a vector function to swap fields and use memory space already made
    this -> children.swap(oth.children);

    return *this;

}

//move constructor implementation
Tree::Tree(Tree &&oth) : node(oth.node), children(move(oth.children)){}

//destructor implementation
Tree::~Tree() {
    for (int i = 0; i < children.size(); i++) //deletes pointers in children vector
        delete children[i];
}

//getter to get node
int Tree::getNode() const {
    return this->node;
}
//getter to get children
std::vector<Tree *> Tree::getChildren() {
    return children;
}

CycleTree::CycleTree(int rootLabel, int currCycle) : Tree(rootLabel), currCycle(currCycle) { //todo
}

int CycleTree::traceTree() {
    Tree* currTree= this;
    for (int i = 0; i < currCycle; ++i) {
        vector<Tree *> children=currTree->getChildren();
        currTree=children[0];
    }
    return currTree->getNode();
}


CycleTree *CycleTree::clone() const {
    return new CycleTree(*this);
}

MaxRankTree::MaxRankTree(int rootLabel) : Tree(rootLabel) { //todo

}
//'pop_front', took from stackoverflow

Tree* pop(std::vector<Tree*>& vec)
{
    Tree* first = vec[0];
    vec.erase(vec.begin());
    return first;
}

int MaxRankTree::traceTree() {
    //first phase: find using BFS what is the max children size
    size_t max_children = 0;
    vector<Tree*> queue;
    cout<< "start BFS" << endl; //todo delete
    queue.push_back(this); ///****
    Tree* curr = pop(queue);
    cout << curr ->getNode() << " , "; //todo delete
    while (!queue.empty()){
        for (auto child : curr -> getChildren())
            queue.push_back(child);
        max_children = max(max_children, curr->getChildren().size()); //compares two things of unsigned longs
    }

    cout <<endl << "end BFS" << endl; //todo delete

    //second phase: find who is the node with most children
    queue.push_back(this);
    while(!queue.empty()) {
        for (auto child : curr->getChildren())
            queue.push_back(child);

        if (curr->getChildren().size() == max_children)
            return curr->getNode();
    }

    return -1;
}

MaxRankTree *MaxRankTree::clone() const {
    return new MaxRankTree(*this);
}

RootTree::RootTree(int rootLabel) : Tree(rootLabel) {

} //todo

int RootTree::traceTree() {
    return getNode();
}

RootTree *RootTree::clone() const { //
    return new RootTree(*this);
}
