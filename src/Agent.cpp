//
// Created by spl211 on 31/10/2020.
//

#include <Agent.h>

Agent::Agent() {}

ContactTracer::ContactTracer() {}

void ContactTracer::act(Session &session) {}

ContactTracer *ContactTracer::clone() const {
    return new ContactTracer(*this);
}


Virus::Virus(int nodeInd) : Agent(), nodeInd(nodeInd){
}


void Virus::act(Session& session) {
    Graph g = session.getGraph();
    if (!g.isInfected(nodeInd)){
        g.infectNode(nodeInd);
        session.enqueueInfected(nodeInd);
    }
    int healthyNeighbor=g.healthyNeighbor(nodeInd);
    if (healthyNeighbor!=-1){
        g.occupyNode(healthyNeighbor);
        Virus virus = Virus(healthyNeighbor);
        session.addAgent(virus);
    }
}

Virus *Virus::clone() const {
        return new Virus(*this);
}






