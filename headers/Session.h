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

    //Copy assignment operator
    Session &operator=(const Session &oth);

    //Move constructor
    Session(Session &&oth);

    //Destructor
    virtual ~Session();



    // Simulates the contact tracing system and creates an output.json for the given session
    //runs in a loop until termination condition is satisfied
    void simulate();

    // Adds new agent to the end of agents vector
    void addAgent(const Agent& agent);

    // Sets the graph g to its new value
    void setGraph(const Graph& graph);

    // Enqueues the infected node index into the infected queue
    void enqueueInfected(int);

    // Dequeues the infected node index from the infected queue
    // Returns: The dequeued node index if exits, else returns -1
    int dequeueInfected();

    //Returns the graph g
    Graph getGraph();

    // Returns: The tree type
    TreeType getTreeType();

    //delete all the agents in the vector agents
    void clearAgents();


    //todo ruleOf5
private:
    Graph g;
    TreeType treeType;
    std::vector<Agent*> agents;
    std:: queue<int> infectionQueue;


};

#endif
