#ifndef AGENT_H_
#define AGENT_H_

#include <vector>
#include "../include/Session.h"
#include "../include/Tree.h"
#include "../include/Graph.h"

class Agent {
public:
    Agent();

    virtual Agent *clone() const = 0;

    virtual void act(Session &session) = 0;


};

class ContactTracer : public Agent {
public:
    ContactTracer();

    // Dequeues an infected node from the infected queue, and tries to break the chain of infection
    //creates shortest path tree from infected node using BFS, uses trace tree method to obtain index of next infected node and removes all edges in graph connecting to it
    virtual void act(Session &session);

    virtual Agent *clone() const;
};


class Virus : public Agent {
public:
    Virus(int nodeInd);

    // Infect the nodes they occupy if not already infected
    // spread themselves into adjacent nodes (virus-free neighbors) in ascending order using node indices
    virtual void act(Session &session);

    virtual Agent *clone() const;


private:
    const int nodeInd;

};

#endif
