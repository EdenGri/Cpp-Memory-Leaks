//
// Created by spl211 on 07/11/2020.
//
#include "Graph.h"
#include "Tree.h"
#include <queue>

using namespace std;

Graph::Graph(std::vector<std::vector<int>> matrix) :
        edges(matrix), infectedList(), occupiedList(), terminateCondition(false), numOfOccupiedNodes(0) {}


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
    for (int i = 0; i < edges.size(); ++i) {
        edges[nodeInd][i] = 0;
        edges[i][nodeInd] = 0;
    }
}

int Graph::healthyNeighbor(int nodeInt) {
    for (int i = 0; i < edges.size(); ++i) {
        int j = edges[nodeInt][i];
        if (j == 1) {
            if (!isOccupied(j)) {
                return j;
            }
        }
    }
    return -1;
}

bool Graph::isTerminateCondition() {
    if (occupiedList.size() != numOfOccupiedNodes) {
        numOfOccupiedNodes = occupiedList.size();
    } else {
        terminateCondition = true;
    }
    return terminateCondition;
}

Tree *Graph::Bfs(Session &session, int node) {
    Tree *output = Tree::createTree(session, node);
    vector<bool> visited(edges.size(), false);
    queue<Tree *> bfsQueue;
    bfsQueue.push(output);
    visited[output->getNode()] = true;
    while (!bfsQueue.empty()) {
        Tree *curr = bfsQueue.front();
        bfsQueue.pop();
        for (int i = 0; i < edges[curr->getNode()].size(); i++) {
            if (edges[curr->getNode()][i] == 1 && !visited[i]) {
                visited[i] = true;
                Tree *tree_temp = Tree::createTree(session, i);
                curr->addChild(*tree_temp);
                bfsQueue.push(tree_temp);
            }


        }
    }
    return output;
}

