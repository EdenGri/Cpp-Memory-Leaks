//
// Created by spl211 on 31/10/2020.
//
#include <fstream>
#include <iostream>
#include <vector>
#include "../include/Session.h"


using namespace std;
using json = nlohmann::json;


Session::Session(const std::string &path) : g({}), treeType(), agents(), infectionQueue(), cycle(0) {
    std::ifstream i(path);
    json j;
    i >> j;
    g = Graph(j["graph"]);
    string tree = j["tree"];
    if (tree == "M")
        treeType = MaxRank;
    else if (tree == "C")
        treeType = Cycle;
    else
        treeType = Root;

    for (auto &elem: j["agents"]) {
        if (elem[0] == "C") {
            Agent *agent = new ContactTracer();
            agents.push_back(agent);
        } else {
            Agent *agent = new Virus(elem[1]);
            agents.push_back(agent);
            g.occupyNode(elem[1]);
        }

    }
}

//copy assignment operator implementation
Session &Session::operator=(const Session &oth) {
    if (this == &oth) {
        return *this;
    } else {
        g = oth.g;
        treeType = oth.treeType;
        clearAgents();
        for (auto agent : oth.agents) {
            agents.push_back(agent->clone());
        }
        infectionQueue = oth.infectionQueue;
        cycle = oth.cycle;
        return *this;
    }

}


Session::Session(const Session &oth) : g(oth.g), treeType(oth.treeType), agents(), infectionQueue(oth.infectionQueue),cycle(oth.cycle) {
    for (auto agent : oth.agents) {
        agents.push_back(agent->clone());
    }
}

//move assignment operator
Session &Session::operator=(Session &&oth) {
    if (&oth != this){
        g = oth.g;
        treeType = oth.treeType;
        this->agents.swap(oth.agents);
        infectionQueue = oth.infectionQueue;
        cycle = oth.cycle;
    }
    return *this;
}

//move constructor implementation
Session::Session(Session &&oth) :
        g(move(oth.g)), treeType(oth.treeType),agents(move(oth.agents)), infectionQueue(move(oth.infectionQueue)), cycle(oth.cycle)
         {}


Session::~Session() {
    clearAgents();
}


void Session::simulate() {
    while (!g.isTerminateCondition()) {
        int cycleSize = agents.size();
        for (int i = 0; i < cycleSize; i++) {
            agents[i]->act(*this);
        }
        cycle++;
    }

    vector<int> infected_vertices;
    for (auto &agent : agents) {
        if (Virus *v = dynamic_cast<Virus *>(agent))
            infected_vertices.push_back(v->getNode());
    }
    //Creates the json file output
    nlohmann::json j;
    j["infected"] = infected_vertices;
    j["graph"] = g.getEdges();
    std::ofstream o("./output.json");
    o << j << std::endl;
}

void Session::addAgent(const Agent &agent) {
    Agent *clone = agent.clone();
    agents.push_back(clone);
}

void Session::setGraph(const Graph &graph) {
    g = graph;
}

int Session::getCycle() const {
    return cycle;
}

Graph &Session::getGraph() {
    return g;
}

void Session::enqueueInfected(int i) {
    infectionQueue.push(i);
}

int Session::dequeueInfected() {
    if (!infectionQueue.empty()) {
        int nodeInd = infectionQueue.front();
        infectionQueue.pop();
        return nodeInd;
    }
    return -1;
}

TreeType Session::getTreeType() const {
    return treeType;
}


void Session::clearAgents() {
    for (auto &agent : agents) {
        delete agent;
    }
    agents.clear();
}

queue<int> &Session::getInfectionQueue() {
    return infectionQueue;
}






