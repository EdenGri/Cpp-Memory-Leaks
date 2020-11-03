//
// Created by spl211 on 31/10/2020.
//
#include <fstream>
#include <iostream>
#include <vector>

#include <Session.h>
#include "json.hpp"


using json = nlohmann::json;

//need to finish initialization list
Session::Session(const std::string &path): g({}){
    std::ifstream  jsonRead(path);
    json jsonParser = json::parse(jsonRead);

    std::cout << jsonParser ["tree"] <<std::endl;

}

void Session::simulate() {

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

