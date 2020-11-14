//
// Created by spl211 on 07/11/2020.
//
#include "../include/Graph.h"
#include <queue>
using namespace std;

Graph::Graph(std::vector<std::vector<int>> matrix) :
        edges(matrix), infectedList(), occupiedList(), numOfOccupiedNodes(0), terminateCondition(false) {}


void Graph::infectNode(int nodeInd) {
    infectedList.insert(nodeInd);
}

bool Graph::isInfected(int nodeInd) {
    // only c++20 contains appropriate function
    return infectedList.find(nodeInd) != infectedList.end();
}

void Graph::occupyNode(int nodeInd) {
    occupiedList.insert(nodeInd);
}


bool Graph::isOccupied(int nodeInd) {
    // only c++20 contains appropriate function
    for (int v:occupiedList)
        if (v == nodeInd)
            return true;
    return false;
}

void Graph::disconnectNode(int nodeInd) {
    for (std::size_t i = 0; i < edges.size(); ++i) {
        edges[nodeInd][i] = 0;
        edges[i][nodeInd] = 0;
    }
}

int Graph::healthyNeighbor(int nodeInt) {
    for (std::size_t i = 0; i < edges.size(); ++i) {
        int is_neighbor = edges[nodeInt][i];
        if (is_neighbor == 1) {
            bool is_oc = isOccupied(i);
            if (!is_oc) {
                return i;
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

Tree* Graph::Bfs(Session &session, int node) {
    Tree* output = Tree::createTree(session, node);
    vector<bool> visited(edges.size(), false);
    queue<Tree*> bfsQueue;
    bfsQueue.push(output);
    visited[node] = true;
    while (!bfsQueue.empty()) {
        Tree* curr = bfsQueue.front();
        bfsQueue.pop();
        vector<int> are_neighbors = edges[curr->getNode()];
        for (std::size_t i = 0; i < are_neighbors.size(); i++) {
            int is_neighbor = are_neighbors[i];
            if (is_neighbor && !visited[i]) {
                visited[i] = true;
                Tree* tree_temp = Tree::createTree(session, i);
                curr->addChild(*tree_temp);

                for (auto c :curr->getChildren())
                    if (c->getNode() == i)
                        bfsQueue.push(c);
                delete (tree_temp);
            }
        }
    }

    return output;
}

std::vector<std::vector<int>> Graph::getEdges() const {
    return edges;
}

