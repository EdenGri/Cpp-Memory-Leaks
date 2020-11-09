//
// Created by spl211 on 31/10/2020.
//
#include <fstream>
#include <iostream>
#include <vector>
#include "Graph.h"
#include <Session.h>
#include "json.hpp"
#include "Agent.h"


using json = nlohmann::json;
using namespace std;
using json = nlohmann::json;


//need to finish initialization list
Session::Session(const std::string &path) : g({}) {
    std::ifstream jsonRead(path);
    json jsonParser = json::parse(jsonRead);

    g = jsonParser["graph"];
    string tree1 = jsonParser["tree"];
    if (tree1 == "M") {

    } else {}
    json jsonFile;
    string jsonTreeType = jsonFile.at("tree");

    if (jsonTreeType == "C") {
        return Cycle;
    } else if (jsonTreeType == "M") {
        return MaxRank;
    } else if (jsonTreeType == "R") {
        return Root;
    }
    std::queue<int> infectionQueue;
    cycle = 0;

    for (auto& elem: jsonParser["agents"]) {
        if(elem[0]=="C"){
            Agent* agent= new ContactTracer();
            agents.push_back(agent);
        } else{
            Agent* agent=new Virus(elem[1]);
            agents.push_back(agent);
        }

    }


}

Session &Session::operator=(const Session &oth) {
    if (this == &oth) {
        return *this;
    } else {
        g= oth.g;
        treeType=oth.treeType;
        infectionQueue=oth.infectionQueue;
        clearAgents();
        for (auto agent : oth.agents) {
            agents.push_back(agent->clone());
        }
        return *this;
    }

}

Session::Session(Session &&oth): g(oth.g),treeType(oth.treeType),infectionQueue(oth.infectionQueue),agents(move(oth.agents))  {}

Session::~Session() {
    clearAgents();
}

Session::Session(const Session &oth) : g(oth.g), treeType(oth.treeType), infectionQueue(oth.infectionQueue){
    for (int i = 0; i < oth.agents.size(); ++i) {
        agents.push_back(oth.agents[i]->clone());
    }
}

Session &Session::operator=(Session &&oth) {
    if (&oth == this) {
        return *this;
    }
    g=oth.g;
    treeType=oth.treeType;
    infectionQueue=oth.infectionQueue;
    this -> agents.swap(oth.agents);
    return *this;
}



void Session::simulate() {
    while (!g.isTerminateCondition()) {
        int cycleSize = agents.size();
        for (int i = 0; i < cycleSize; i++) {
            agents[i]->act(*this); //todo check
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




void Session::clearAgents() {
    for (auto & agent : agents) {
        delete agent;
    }
    agents.clear();
}

queue<int> Session::getInfectionQueue() {
    return infectionQueue;
}

TreeType Session::getTreeType() const {
    return treeType;
}






