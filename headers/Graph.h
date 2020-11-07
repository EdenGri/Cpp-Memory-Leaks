#ifndef GRAPH_H_
#define GRAPH_H_

#include <set>
#include <vector>

class Graph{
public:
    // Creates graph with the given adjacency matrix
    Graph(std::vector<std::vector<int>> matrix);

    // Adds the given infected node index to the infected list
    void infectNode(int nodeInd);

    // Returns: True if the node is infected, else returns false
    bool isInfected(int nodeInd);

    // Adds the given node index to the occupied list
    void occupyNode(int nodeInd);

    // Returns: True if the node is occupied, else returns false
    bool isOccupied(int nodeInd);

    // Disconnects node from the graph. remove the edges that contains the given node
    void disconnectNode(int nodeInd);

    //Return the index of the next healthy node neighbor that "nodeInd" should occupy
    int healthyNeighbor(int nodeInd);
    bool isChainBreak();

private:
    std::vector<std::vector<int>> edges;
    std::set<int> infectedList;
    std::set<int> occupiedList;
    int numOfOccupiedNodes;
    bool chainBreak;

};

#endif
