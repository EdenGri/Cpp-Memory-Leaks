//
// Created by spl211 on 31/10/2020.
//
#include <queue>
#include "../include/Agent.h"
#include "../include/Session.h"

Agent::Agent() {}

ContactTracer::ContactTracer() : Agent() {}


Agent* ContactTracer::clone() const {
    return new ContactTracer(*this);
}


void ContactTracer::act(Session &session) {
    std::queue<int> infectionQueue = session.getInfectionQueue();
    if (!infectionQueue.empty()) {
        int infectedNode = infectionQueue.back(); //todo check
        Graph g = session.getGraph();
        Tree *tree = session.getGraph().Bfs(infectedNode, session);
        g.disconnectNode(tree->traceTree());
    }
}


Agent *ContactTracer::clone() const {
    return new ContactTracer(*this);
}


Virus::Virus(int nodeInd) : Agent(), nodeInd(nodeInd) {
}

Agent* Virus::clone() const {
    return new Virus(*this);
}

void Virus::act(Session& session) {
    Graph g = session.getGraph();
    if (!g.isInfected(nodeInd)) {
        g.infectNode(nodeInd);
        session.enqueueInfected(nodeInd);
    }
    int healthyNeighbor = g.healthyNeighbor(nodeInd);
    if (healthyNeighbor != -1) {
        g.occupyNode(healthyNeighbor);
        Virus virus = Virus(healthyNeighbor);
        session.addAgent(virus);
    }
}









