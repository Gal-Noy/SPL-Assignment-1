#include "Simulation.h"
#include <utility>

Simulation::Simulation(Graph graph, vector<Agent> agents) : mGraph(std::move(graph)), mAgents(std::move(agents)),
                                                            mCoalitions(vector<Coalition>{}), mParties(map<unsigned int, int>{})  {
    // Reserve enough memory for maximum amount of agents
    mAgents.reserve(mGraph.getNumVertices());

    // Initialize coalition for each agent
    for (unsigned int i = 0; i < mAgents.size(); i++){
        Agent &agent = mAgents[i];
        agent.setCoalition(i);
        Coalition agentCoalition(agent.getId());

        // Add agent's party to its coalition
        Party &party = mGraph.getPartyById(agent.getPartyId());
        agentCoalition.addParty(party);

        mCoalitions.push_back(agentCoalition);
    }

    // Initialize timers for each party (set to -1)
    vector<Party> &parties = mGraph.getParties();
    for (unsigned int i = 0; i < parties.size(); i++) {
        mParties[i] = -1;
    }
}

void Simulation::step() {

    // Parties step: iterate each party and invoke "step"
    vector<Party> &parties = mGraph.getParties();
    for (unsigned int i = 0; i < parties.size(); i++) {
        Party &party = parties[i];
        if (party.getState() == CollectingOffers) {
            if (mParties[i] != 0) {
                if (mParties[i] == -1)
                    mParties[i] = 1;
                else
                    mParties[i]--;
            }
            else
                party.step(*this);
        }
    }

    // Agents step: iterate each agent and invoke "step"
    for (Agent &agent: mAgents) {
        agent.step(*this);
    }
}

bool Simulation::shouldTerminate() const {

    // Check coalitions and return true if mandates >= 61
    vector<vector<int>> politicalMap = getPartiesByCoalitions();
    int mandates = 0;
    int totalMandates = 0;
    for (vector<int> &coalition: politicalMap) {
        for (int partyId: coalition) {
            mandates += getParty(partyId).getMandates();
            if (mandates > 60)
                return true;
        }
        totalMandates += mandates;
        mandates = 0;
    }

    // If we summed 120 mandates from the coalitions, then every party is "Joined"
    if (totalMandates == 120) return true;

    return false;
}

Coalition &Simulation::getCoalition(int coalitionId){
    return mCoalitions[coalitionId];
}

const Graph &Simulation::getGraph() const {
    return mGraph;
}

Graph &Simulation::getGraph(){
    return mGraph;
}

const vector<Agent> &Simulation::getAgents() const {
    return mAgents;
}

const Party &Simulation::getParty(int partyId) const {
    return mGraph.getParty(partyId);
}

/// This method returns a "coalition" vector, where each element is a vector of party IDs in the coalition.
/// At the simulation initialization - the result will be [[agent0.partyId], [agent1.partyId], ...]
const vector<vector<int>> Simulation::getPartiesByCoalitions() const {
    vector<vector<int>> ans;
    for (const Coalition &coalition : mCoalitions)
        ans.push_back(coalition.getExistingParties());
    return ans;
}

void Simulation::cloneAgent(int agentId, int partyId) {
    Agent &agentToClone = mAgents[agentId];
    Agent toAdd(mAgents.size(), partyId, agentToClone.getSelectionPolicy()->clone());
    toAdd.setCoalition(agentToClone.getCoalitionId());
    mAgents.push_back(toAdd);
}