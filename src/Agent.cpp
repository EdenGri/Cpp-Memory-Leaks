//
// Created by spl211 on 31/10/2020.
//

#include <Agent.h>

Agent::Agent(Session& session): session(session) {

}

// ContactTracer::ContactTracer(Session &session) : Agent(session) {}

//Virus::Virus(int nodeInd, Session &session) : Agent(session), nodeInd(nodeInd) {
//}

/*void Virus::act(Session& session) {
    Graph g = session.getGraph();
    if (!g.isInfected(nodeInd)){
        g.infectNode(nodeInd);
        session.enqueueInfected(nodeInd);
    }
    int healthyNeighbor=g.healthyNeighbor(nodeInd);
    if (healthyNeighbor!=-1 ){
        g.occupyNode(healthyNeighbor);
    } else{

    }

}*/


