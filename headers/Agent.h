#ifndef AGENT_H_
#define AGENT_H_

#include <vector>
#include "Session.h"

class Agent{
public:
    Agent(Session& session);
    
    virtual void act(Session& session)=0;

private:
    Session& session;
};

class ContactTracer: public Agent{
public:
    ContactTracer(Session& session);

    // Dequeues an infected node from the infected queue, and tries to break the chain of infection
    //creates shortest path tree from infected node using BFS, uses tracetree() method to obtain index of next infected node and removes all edges in graph connecting to it
    virtual void act(Session& session);

};


class Virus: public Agent{
public:
    Virus(int nodeInd, Session& session);
    // Infect the nodes they occupy if not already infected
    // spread themselves into adjacent nodes (virus-free neighbors) in ascending order using node indices
    virtual void act(Session& session);


private:
    const int nodeInd;
};

#endif
