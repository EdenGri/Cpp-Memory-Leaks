#ifndef SESSION_H_
#define SESSION_H_

#include <vector>
#include <string>
#include "Graph.h"

class Agent;

enum TreeType{
  Cycle,
  MaxRank,
  Root
};

class Session{
public:
    // Creates a session from a given config.json filepath.
    Session(const std::string& path);

    // Simulates the contact tracing system and creates an output.json for the given session.
    void simulate();

    // Adds new agent to the end of agents vector.
    void addAgent(const Agent& agent);

    // Sets the graph g to it's new value.
    void setGraph(const Graph& graph);

    // Enqueues the infected node index to the infected queue.
    void enqueueInfected(int);

    // Dequeues the infected node index from the infected queue.
    // Returns: The dequeued node index if exits, else returns -1.
    int dequeueInfected();

    // Returns: The tree type.
    TreeType getTreeType();
    
private:
    Graph g;
    TreeType treeType;
    std::vector<Agent*> agents;
};

#endif
