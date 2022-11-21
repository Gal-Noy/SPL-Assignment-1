#pragma once

#include <vector>
#include <map>

#include "Graph.h"
#include "Agent.h"

using std::string;
using std::vector;
using std::map;

using namespace std;

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
    void addJoinedMandates(int mandates);
    void setMaxMandates(int coalitionMandates);

private:
    Graph mGraph;
    vector<Agent> mAgents;
    vector<Coalition> mCoalitions;
    int maxMandatesCoalition;
    int joinedMandates;
};