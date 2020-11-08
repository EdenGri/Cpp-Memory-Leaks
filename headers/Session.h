#ifndef SESSION_H_
#define SESSION_H_

#include <vector>
#include <string>
#include <queue>
#include "Graph.h"
#include "Agent.h"

class Agent;

enum TreeType{
  Cycle,
  MaxRank,
  Root
};

class Session{
public:
    // Creates a session from a given config.json filepath
    Session(const std::string& path);

    // Simulates the contact tracing system and creates an output.json for the given session
    //runs in a loop until termination condition is satisfied
    void simulate();

    // Adds new agent to the end of agents vector
    void addAgent(const Agent& agent);

    // Sets the graph g to its new value
    void setGraph(const Graph& graph);

    // Graph getter
    Graph getGraph() const;

    // Enqueues the infected node index into the infected queue
    void enqueueInfected(int);

    // Dequeues the infected node index from the infected queue
    // Returns: The dequeued node index if exits, else returns -1
    int dequeueInfected();

    // Returns: The tree type
    TreeType getTreeType();

    //helper function added that returns cycle number
    int getCycleNum() const;

    //copy constructor
    Session(const Session &oth);

    //move assignment operator
    Session &operator=(Session &&oth);

private:
    Graph g;
    TreeType treeType;
    std::vector<Agent*> agents;
    std:: queue<int> infectionQueue;
    int cycle;


};

#endif
