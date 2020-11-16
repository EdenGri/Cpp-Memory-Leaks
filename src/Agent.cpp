//
// Created by spl211 on 31/10/2020.
//
#include <queue>
#include "../include/Agent.h"
#include "../include/Session.h"

Agent::Agent() {}

ContactTracer::ContactTracer() : Agent() {}


Agent *ContactTracer::clone() const {
    return new ContactTracer(*this);
}


void ContactTracer::act(Session &session) {
    std::queue<int> &infectionQueue = session.getInfectionQueue();
    //dequeues infected node from queue
    if (!infectionQueue.empty()) {
        int infectedNode = infectionQueue.front();
        infectionQueue.pop();
        Graph &g = session.getGraph();
        Tree *tree = g.Bfs(session, infectedNode);
        //finds next infected node and disconnects from graph
        int deadly = tree->traceTree();
        g.disconnectNode(deadly);
        if (tree != nullptr) { //todo check
            delete tree;
        }
        tree = nullptr;
    }
}


Virus::Virus(int nodeInd) : Agent(), nodeInd(nodeInd) {
}

Agent *Virus::clone() const {
    return new Virus(*this);
}

void Virus::act(Session &session) {
    Graph &g = session.getGraph();
    //infects node if not already infected
    if (!g.isInfected(nodeInd)) {
        g.infectNode(nodeInd);
        session.enqueueInfected(nodeInd);
    }
    //spreads into uninfected neighbor nodes
    int healthyNeighbor = g.healthyNeighbor(nodeInd);
    if (healthyNeighbor != -1) {
        g.occupyNode(healthyNeighbor);
        Virus virus = Virus(healthyNeighbor);
        session.addAgent(virus);
    }
}

int Virus::getNode() const {
    return nodeInd;
}









