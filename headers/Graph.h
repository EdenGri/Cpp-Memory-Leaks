#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>

class Graph{
public:
    // Creates graph with the given adjacent matrix
    Graph(std::vector<std::vector<int>> matrix);

    // Adds the given infected node index to the infected list.
    void infectNode(int nodeInd);

    // Returns: True if the node is infected, else return false.
    bool isInfected(int nodeInd);
private:
    std::vector<std::vector<int>> edges;
};

#endif
