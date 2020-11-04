#ifndef GRAPH_H_
#define GRAPH_H_

#include <set>
#include <vector>

class Graph{
public:
    // Creates graph with the given adjacent matrix
    Graph(std::vector<std::vector<int>> matrix);

    // Adds the given infected node index to the infected list.
    void infectNode(int nodeInd);

    // Returns: True if the node is infected, else return false.
    bool isInfected(int nodeInd);

    // Adds the given node index to the occupies list.
    void occupyNode(int nodeInd);

    // Returns: True if the node is occupied, else return false.
    bool isOccupies(int nodeInd);

    // Disconnects node from the graph. remove the edges that contains the given node.
    void disconnectNode(int nodeInd);

private:
    std::vector<std::vector<int>> edges;
    std::set<int> infectedList;
    std::set<int> occupiesList;


};

#endif
