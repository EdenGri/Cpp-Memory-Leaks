//
// Created by spl211 on 31/10/2020.
//
#include <fstream>
#include <iostream>
#include <vector>
#include "Graph.h"
#include <Session.h>
#include "json.hpp"

using namespace std;
using json = nlohmann::json;


//need to finish initialization list
Session::Session(const std::string &path): g({}), treeType(), agents(){
    std::ifstream jsonRead(path);
    json jsonParser = json::parse(jsonRead);

    vector <pair<string, int>> agents1 = jsonParser["agents"];
    vector<vector<int>> graph1 = jsonParser["graph"];
    string tree1 = jsonParser["tree"];

    g= graph1;
    if(tree1 == "M"){

    }
    else{}

    std::queue<int> infectionQueue;

    for (auto& elem: jsonParser["agents"]) {

        Agent agent;
        if(elem[0]=="C"){
            ContactTracer agent(this);
        } else{
            Virus agent(this,elem[1]);
        }
        agents.push_back(agent);
    }


}

void Session::simulate() {
    while (!g.isChainBreak()){
        int cycleSize=agents.size();
        for(int i=0; i < cycleSize;i++){
            agents[i]->act(this);
        }
    }
}

void Session::addAgent(const Agent &agent) {
    agents.push_back(agent);
}

void Session::setGraph(const Graph &graph) {
    g = graph;
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

TreeType Session::getTreeType() {
    json jsonFile;
    string jsonTreeType = jsonFile.at("tree");

    if (jsonTreeType == "C") {
        return Cycle;
    }
    else if (jsonTreeType == "M") {
        return MaxRank;
    }
    else if (jsonTreeType == "R") {
        return Root;
    }
}


Graph Session::getGraph() {
    return g;
}

