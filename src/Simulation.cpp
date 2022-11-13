#include "Simulation.h"
#include "Agent.h"
#include "Graph.h"
#include <map>

Simulation::Simulation(Graph graph, vector<Agent> agents) : mGraph(graph), mAgents(agents) 
{
    // 1. init coalitions:
    // 1.1. for every agent form a coalition (mandates & availableParties)
    // 1.2. init firstly available parties

}

void Simulation::step()
{
    const Graph &graph = getGraph();
    for (int i = 0; i < graph.getNumVertices(); i++){
        Party party = graph.getParty(i);
        party.step(*this);
    }

    for (Agent agent : mAgents){
        agent.step(*this);
    }
    // 1. parties-step: parties that can answer offers, answer 
    // 2. agents-step: select party to offer and offer
}

bool Simulation::shouldTerminate() const
{
    // should terminate when any coalition reaches 61 mandates or all parties are in state joined

    // check coalitions and return true if mandates >= 61 
    // check parties and count waiting/collecting offers and return == 0
    // heap? boolean value? stay tuned

    // TODO implement this method
    return true;
}

const Graph &Simulation::getGraph() const
{
    return mGraph;
}

const vector<Agent> &Simulation::getAgents() const
{
    return mAgents;
}

const Party &Simulation::getParty(int partyId) const
{
    return mGraph.getParty(partyId);
}

/// This method returns a "coalition" vector, where each element is a vector of party IDs in the coalition.
/// At the simulation initialization - the result will be [[agent0.partyId], [agent1.partyId], ...]
const vector<vector<int>> Simulation::getPartiesByCoalitions() const
{
    // std::map<int, vector<int>> map;
    // for (Agent agent : getAgents()){
    //     if (map.find(agent.getCoalition()) == map.end())
    //         map[agent.getCoalition()] = vector<int>();
    //     map[agent.getCoalition()].push_back(agent.getPartyId());
    // }
    // vector<vector<int>> ans;
    // for (auto coalitionVector : map)
    //     ans.push_back(coalitionVector.second);
    // return ans;
}


