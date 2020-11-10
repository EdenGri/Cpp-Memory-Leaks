//
// Created by spl211 on 31/10/2020.
//
#include <fstream>
#include <iostream>
#include <vector>
#include "../include/Session.h"




using namespace std;
using json = nlohmann::json;


Session::Session(const std::string &path) : g({}) {
    std::ifstream i(path);
    json j;
    i >> j;
    g = Graph(j["graph"]);
    string tree = j["tree"];
    if (tree == "M")
        treeType = MaxRank;
    else if(tree == "C")
        treeType = Cycle;
    else
        treeType = Root;

    for (auto& elem: j["agents"]) {
        if(elem[0]=="C"){
            Agent* agent= new ContactTracer();
            agents.push_back(agent);
        } else{
            Agent* agent= new Virus(elem[1]);
            agents.push_back(agent);
        }

    }
    cycle = 0;
    //todo check if we need to initialize ocuupiedlist


}

Session &Session::operator=(const Session &oth) {
    if (this == &oth) {
        return *this;
    } else {
        g = oth.g;
        cycle = oth.cycle;
        treeType=oth.treeType;
        infectionQueue=oth.infectionQueue;
        clearAgents();
        for (auto agent : oth.agents) {
            agents.push_back(agent->clone());
        }
        return *this;
    }

}

Session::Session(Session &&oth):
g(move(oth.g)),treeType(oth.treeType),infectionQueue(move(oth.infectionQueue)), cycle(oth.cycle),agents(move(oth.agents)){}

Session::~Session() {
    clearAgents();
}

Session::Session(const Session &oth) : g(oth.g), treeType(oth.treeType), infectionQueue(oth.infectionQueue), cycle(oth.cycle){
    for (int i = 0; i < oth.agents.size(); ++i) {
        agents.push_back(oth.agents[i]->clone());
    }
}

Session &Session::operator=(Session &&oth) {
    if (&oth != this) {
        g = oth.g;
        cycle = oth.cycle;
        treeType = oth.treeType;
        infectionQueue = oth.infectionQueue;
        this->agents.swap(oth.agents);
    }
    return *this;
}



void Session::simulate() {
    while (!g.isTerminateCondition()) {
        int cycleSize = agents.size();
        for (int i = 0; i < cycleSize; i++) {
            agents[i]->act(*this);
        }
        cycle++;
    }
}

void Session::addAgent(const Agent &agent) {
    Agent *clone = agent.clone();
    agents.push_back(clone);
}

void Session::setGraph(const Graph &graph) {
    g = graph;
}

int Session:: getCycle() const{
    return cycle;
}

Graph Session::getGraph() const {
    return g;
}

void Session::enqueueInfected(int i) {
    infectionQueue.push(i);
}

int Session::dequeueInfected() {
    if (!infectionQueue.empty()) {
        return infectionQueue.back();
    }
    return -1;
}

TreeType Session::getTreeType() const {
    return treeType;
}



void Session::clearAgents() {
    for (auto & agent : agents) {
        delete agent;
    }
    agents.clear();
}

queue<int> Session::getInfectionQueue() {
    return infectionQueue;
}






