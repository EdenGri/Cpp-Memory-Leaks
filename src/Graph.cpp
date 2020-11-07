//
// Created by spl211 on 07/11/2020.
//
#include "Graph.h"



Graph::Graph(std::vector<std::vector<int>> matrix) : edges(matrix) , infectedList(), occupiedList(),chainBreak(false),numOfOccupiedNodes(0){}


void Graph::infectNode(int nodeInd) {
    infectedList.insert(nodeInd);
}
bool Graph::isInfected(int nodeInd) {
    // just in set c++20 theres contains function.
    return infectedList.find(nodeInd) != infectedList.end();
}

void Graph::occupyNode(int nodeInd) {
    occupiedList.insert(nodeInd);
}

bool Graph::isOccupied(int nodeInd) {
    // just in set c++20 theres contains function.
    return occupiedList.find(nodeInd) != occupiedList.end();
}

void Graph::disconnectNode(int nodeInd) {
    for (int i = 0; i <edges.size() ; ++i) {
        edges[nodeInd][i]=0;
        edges[i][nodeInd]=0;
    }
}

int Graph::healthyNeighbor(int nodeInt) {
    for (int i = 0; i < edges.size(); ++i) {
        int j = edges[nodeInt][i];
        if (j==1){
            if (!isOccupied(j)) {
                return j;
            }
        }
    }
    return -1;
}

bool Graph::isChainBreak() {
    if (occupiedList.size()!=numOfOccupiedNodes){
        numOfOccupiedNodes=occupiedList.size();
    } else{
        chainBreak= true;
    }
    return chainBreak;
}

