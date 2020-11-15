#ifndef TREE_H_
#define TREE_H_

#include <vector>


class Session;
class Tree {
public:
    Tree(int rootLabel);

    //Adds a copy of the child to children vector while keeping the sorting order by label
    void addChild(const Tree &child);
    //Creates empty tree (just with a root label) according to tree type
    static Tree *createTree(const Session &session, int rootLabel);

    //Returns index of node in the graph which contact tracers should disconnect
    virtual int traceTree() = 0;

    //Creates a copy of the specific tree
    virtual Tree *clone() const = 0;

    //Getter of the node label
    int getNode() const;

    //Getter of the children
    std::vector<Tree *> getChildren();

    //Copy constructor
    Tree(const Tree &oth);

    //Copy assignment operator
    Tree &operator=(const Tree &oth);

    //Move assignment operator
    Tree &operator=(Tree &&oth);

    //Move constructor
    Tree(Tree &&oth);

    //Destructor
    virtual ~ Tree();


private:
    int node;
    std::vector<Tree *> children;
};

//Traverses tree from root always picking left-most child
//Returns c'th node in this trip, where c is the cycle in which the tree was created
//If the trip is less than c nodes long, returns the last node in it.
class CycleTree : public Tree {
public:
    CycleTree(int rootLabel, int currCycle);

    virtual int traceTree();

    virtual CycleTree *clone() const;


private:
    int currCycle;
};

//Returns index of node in tree with highest num of children, if tied pick node with smallest depth, if tied left-most node will be picked
class MaxRankTree : public Tree {
public:
    MaxRankTree(int rootLabel);

    virtual int traceTree();

    virtual MaxRankTree *clone() const;

};

//Returns index of root of the tree
class RootTree : public Tree {
public:
    RootTree(int rootLabel);

    virtual int traceTree();

    virtual RootTree *clone() const;

};

#endif
