//
// Created by spl211 on 31/10/2020.
//

#include "../include/Tree.h"
#include <iostream>
#include "../include/Session.h"


using namespace std;

Tree::Tree(int rootLabel) : node(rootLabel), children() {
}

void Tree::addChild(const Tree &child) {
    vector<Tree*> &vec_old = this->children;
    Tree* item = child.clone();
    vector<Tree*> vec_new;
    if (vec_old.empty()) {
        vec_old.push_back(item);
        return;
    }
    //finds appropriate place according to child's label
    std::size_t i = 0;
    for (; i < vec_old.size() && vec_old[i]->node < item->node; i++) {
        if (vec_old[i]->node < item->node)
            vec_new.push_back(
                    (vec_old[i]));
    }
    vec_new.push_back(item);
    for (; i < vec_old.size(); i++)
        vec_new.push_back(vec_old[i]);

    this->children = vec_new;
}

Tree* Tree::createTree(const Session &session, int rootLabel) {
    TreeType type = session.getTreeType();
    Tree* output;
    switch (type) {
        case Cycle:
            output = new CycleTree(rootLabel, session.getCycle());
            break;
        case MaxRank:
            output = new MaxRankTree(rootLabel);
            break;
        case Root:
            output = new RootTree(rootLabel);
            break;
    }
    return output;

}


Tree::Tree(const Tree &oth) : node(oth.node), children() {
    for (Tree* p_child : oth.children) {
        this->addChild(*p_child);
    }
}

//Copy assignment operator implementation
Tree &Tree::operator=(const Tree &oth) {
    if (this != &oth) {
        this->node = oth.node; //updates node field

        //clears existing children list
        for (auto &i : children) {
            if (i != nullptr) { //todo check
                //deletes pointers in me vector
                delete i;
            }
            i = nullptr;
        }

        children.clear(); //clears vector and makes it size 0

        //Add new children list from other vector
        for (auto i : oth.children)
            children.push_back(i->clone());
    }
    return *this;
}

//Move assignment operator implementation
Tree &Tree::operator=(Tree &&oth) {
    if (&oth != this) {
        this->node = oth.node;

        //swap is a vector function to swap fields and uses memory space already made
        this->children.swap(oth.children);
    }
    return *this;

}

//Move constructor implementation
Tree::Tree(Tree &&oth) : node(oth.node), children(move(oth.children)) {}


Tree::~Tree() {
        for (auto & i : children) {
            if(i != nullptr) {
                //deletes pointers in children vector
                delete i;
            }
            i = nullptr;
        }
}


int Tree::getNode() const {
    return this->node;
}


std::vector<Tree*> Tree::getChildren() {
    return children;
}

CycleTree::CycleTree(int rootLabel, int currCycle) : Tree(rootLabel), currCycle(currCycle) {
}

int CycleTree::traceTree() {
    Tree* currTree = this;
    for (int i = 0; i < currCycle && !currTree->getChildren().empty(); ++i) {
        vector<Tree*> children = currTree->getChildren();
        currTree = children[0];
    }
    return currTree->getNode();
}


CycleTree* CycleTree::clone() const {
    return new CycleTree(*this);
}

MaxRankTree::MaxRankTree(int rootLabel) : Tree(rootLabel) {

}

Tree* pop(std::vector<Tree*> &vec) {
    Tree* first = vec[0];
    vec.erase(vec.begin());
    return first;
}

int MaxRankTree::traceTree() {
    size_t max_children = 0;
    int output(-1);
    vector<Tree*> queue;
    queue.push_back(this);
    while (!queue.empty()) {
        Tree* curr = pop(queue);
        vector<Tree*> curr_children = curr->getChildren();
        for (auto child : curr_children) {
            queue.push_back(child);
        }
        if (curr->getChildren().size() > max_children || max_children==0) {
            max_children = curr->getChildren().size();
            output = curr->getNode();
        }
    }
    return output;
}

MaxRankTree* MaxRankTree::clone() const {
    return new MaxRankTree(*this);
}

RootTree::RootTree(int rootLabel) : Tree(rootLabel) {
}

int RootTree::traceTree() {
    return getNode();
}

RootTree* RootTree::clone() const {
    return new RootTree(*this);
}
