#ifndef SESSION_H_
#define SESSION_H_

#include <vector>
#include <string>
#include <queue>
#include "../include/Graph.h"
#include "../include/Agent.h"
#include "../include/json.hpp"

enum TreeType {
    Cycle,
    MaxRank,
    Root
};

class Session {
public:
    // Creates a session from a given config.json filepath
    Session(const std::string &path);

    //Copy constructor
    Session(const Session &oth);

    //Copy assignment operator
    Session &operator=(const Session &oth);

    //move assignment operator
    Session &operator=(Session &&oth);

    //Move constructor
    Session(Session &&oth);

    //Destructor
    virtual ~Session();

    // Simulates the contact tracing system and creates an output.json for the given session
    //runs in a loop until termination condition is satisfied
    void simulate();

    // Adds new agent to the end of agents vector
    void addAgent(const Agent &agent);

    // Sets the graph g to its new value
    void setGraph(const Graph &graph);

    //Graph Getter
    Graph getGraph() const;

    // Enqueues the infected node index into the infected queue
    void enqueueInfected(int);

    // Dequeues the infected node index from the infected queue
    // Returns: The dequeued node index if exits, else returns -1
    int dequeueInfected();

    //cycle getter
    int getCycle() const;

    // Returns: The tree type
    TreeType getTreeType() const;

    //delete all the agents in the vector agents
    void clearAgents();

    //Return infectionQueue
    std::queue<int> getInfectionQueue();

private:
    Graph g;
    TreeType treeType;
    std::vector<Agent *> agents;
    std::queue<int> infectionQueue;
    int cycle;


    void setGraph(const Graph &graph);
};

#endif
