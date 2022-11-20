#pragma once

#include <vector>
#include <map>

#include "Graph.h"
#include "Agent.h"

using std::string;
using std::vector;
using std::map;

class Simulation {
public:
    Simulation(Graph g, vector<Agent> agents);

    void step();
    bool shouldTerminate() const;
    const Graph &getGraph() const;
    Graph &getGraph();
    const vector<Agent> &getAgents() const;
    Coalition &getCoalition(int coalitionId);
    const Party &getParty(int partyId) const;
    const vector<vector<int>> getPartiesByCoalitions() const;
    void cloneAgent(int agentId, int partyId);

private:
    Graph mGraph;
    vector<Agent> mAgents;
    vector<Coalition> mCoalitions;
    map<unsigned int, int> mParties;
};