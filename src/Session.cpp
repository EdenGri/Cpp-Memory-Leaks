//
// Created by spl211 on 31/10/2020.
//
#include <fstream>
#include <iostream>
#include <vector>

#include <Session.h>
#include "json.hpp"


using json = nlohmann::json;
using namespace std;

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
        for (Agent agent:agents) {
            agent.act();
        }

    }
    return;

}

void Session::addAgent(const Agent &agent) {

}

void Session::setGraph(const Graph &graph) {

}

void Session::enqueueInfected(int) {

}

int Session::dequeueInfected() {
    return 0;
}

TreeType Session::getTreeType() {
    return Cycle;
}

