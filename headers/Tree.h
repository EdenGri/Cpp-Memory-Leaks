#ifndef TREE_H_
#define TREE_H_

#include <vector>

class Session;

class Tree {
public:
    Tree(int rootLabel);

    void addChild(const Tree &child);


    static Tree *createTree(const Session &session, int rootLabel);

    virtual int traceTree() = 0;

    virtual Tree * clone() = 0 const;

    Tree(const Tree &oth);

private:
    int node;
    std::vector<Tree *> children;
};

class CycleTree : public Tree {
public:
    CycleTree(int rootLabel, int currCycle);

    virtual int traceTree();

    virtual CycleTree *clone();

    CycleTree(const CycleTree &oth);

private:
    int currCycle;
};

class MaxRankTree : public Tree {
public:
    MaxRankTree(int rootLabel);

    virtual int traceTree();

    virtual MaxRankTree *clone();

};

class RootTree : public Tree {
public:
    RootTree(int rootLabel);

    virtual int traceTree();

    virtual RootTree *clone();

};

#endif