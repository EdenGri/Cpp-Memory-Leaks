#ifndef TREE_H_
#define TREE_H_

#include <vector>
#include "Session.h"

class Tree {
public:
    Tree(int rootLabel);

    //adds child to children vector while keeping the sorting order by label
    void addChild(const Tree &child);

    //"put all ifs here" todo delete
    static Tree *createTree(const Session &session, int rootLabel);

    //returns index of node in the graph which contact tracers should disconnect
    virtual int traceTree() = 0;

    //clone creates a copy of the specific tree
    virtual Tree *clone() const = 0;

    //const cause it does not change "this"
    int getNode() const;

    std::vector<Tree*> getChildren();

    //copy constructor
    Tree(const Tree &oth);

    //copy assignment operator
    Tree &operator=(const Tree &oth);

    //move assignment operator
    Tree &operator=(Tree &&oth);

    //move constructor
    Tree(Tree &&oth);

    //destructor
    virtual ~ Tree();


private:
    int node;
    std::vector<Tree *> children;
};

//traverses tree from root always picking left-most child
//returns c'th node in this trip, where c is the cycle in which the tree was created
//If the trip is less than c nodes long, returns the last node in it.
class CycleTree : public Tree {
public:
    CycleTree(int rootLabel, int currCycle);

    virtual int traceTree();

    virtual CycleTree *clone() const;


private:
    int currCycle;
};

//returns index of node in tree with highest num of children, if tied pick node with smallest depth, if tied left-most node will be picked
class MaxRankTree : public Tree {
public:
    MaxRankTree(int rootLabel);

    virtual int traceTree();

    virtual MaxRankTree *clone() const;

};

//returns index of root of the tree
class RootTree : public Tree {
public:
    RootTree(int rootLabel);

    virtual int traceTree();

    virtual RootTree *clone() const;

};

#endif
