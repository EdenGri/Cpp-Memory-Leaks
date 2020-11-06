//
// Created by spl211 on 31/10/2020.
//

#include <Tree.h>

using namespace std;

Tree::Tree(int rootLabel) : node(rootLabel), children() {

}

void Tree::addChild(const Tree &child) {
    vector<Tree *> &vec_old = this->children;
    Tree *item = child.clone();
    vector<Tree *> vec_new = vector<Tree *>(); // vector<Tree*> vec_new; calls empty
    if (vec_old.empty()) {
        vec_old.push_back(item);
        return;
    }
    int i = 0;
    for (; vec_old[i]->node < item->node; i++) {
        if (vec_old[i]->node < item->node)
            vec_new.push_back(
                    (vec_old[i])); // we did push back to pointer and therefore dont need to delete old pointers and there is no memory leak
    }
    vec_new.push_back(item);
    for (; i < vec_old.size(); i++)
        vec_new.push_back(vec_old[i]);

    this->children = vec_new;
}

Tree *Tree::createTree(const Session &session, int rootLabel) {
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

    this->node = oth.node;

    //clear existing children list
    //we can press on highlighted for and make prettier for
    for (int i = 0; i < children.size(); i++) //deletes pointers in vector
        delete children[i];

    children.clear(); //clears vector and makes his size 0

    //Add new children list
    for (int i = 0; i < oth.children.size(); i++)
        children.push_back(oth.children[i]->clone()); //creates new location on heap using clone (deep-copy)

    return *this;
}

//move assignment operator implementation ****??
Tree &Tree::operator=(Tree &&oth) {
    if (&oth == this)
        return *this;

    this->node = oth.node;

    this -> children.swap(oth.children);
    //swap is a vector function to swap fields and use memory space already made

    return *this;

}

//move constructor implementation ***??
Tree::Tree(Tree &&oth) : node(oth.node), children(move(oth.children)){}

//destructor implementation
Tree::~Tree() {
    for (int i = 0; i < children.size(); i++) //deletes pointers in vector
        delete children[i];
}

int Tree::getNode() const { //getter to get node
    return this->node;
}

CycleTree::CycleTree(int
                     rootLabel, int
                     currCycle) : Tree(rootLabel), currCycle(currCycle) {

}

int CycleTree::traceTree() {
    return 0;
}


CycleTree *CycleTree::clone() const {
    return new CycleTree(*this);
}

MaxRankTree::MaxRankTree(int
                         rootLabel) : Tree(rootLabel) {

}
//'pop_front', took from stackoverflow

Tree* pop(std::vector<Tree*>& vec)
{
    Tree* first = vec[0];
    vec.erase(vec.begin());
    return first;
}

int MaxRankTree::traceTree() {
    int max_children = 0;
    vector<Tree*> queue;
    queue.push_back(this);
    while (!queue.empty()){
        Tree* curr = pop(queue);
    }
    return 0;
}

MaxRankTree *MaxRankTree::clone() const {
    return new MaxRankTree(*this);
}

RootTree::RootTree(int
                   rootLabel) : Tree(rootLabel) {

}

int RootTree::traceTree() {
    return getNode();
}

RootTree *RootTree::clone() const {
    return new RootTree(*this);
}
