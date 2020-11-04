#ifndef AGENT_H_
#define AGENT_H_

#include <vector>
#include "Session.h"

class Agent{
public:
    Agent(Session& session);
    
    virtual void act()=0;
private:
    Session& session;
};

class ContactTracer: public Agent{
public:
    ContactTracer(Session& session);

    // Dequeues an infected node index from the infected queue, and tries to break the infection chain from that node.
    virtual void act();
};


class Virus: public Agent{
public:
    Virus(int nodeInd, Session& session);
    // Infects the node they occupy and spreads themselves into adjacent nodes(by creating new virus).
    virtual void act();
private:
    const int nodeInd;
};

#endif
