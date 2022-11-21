#include "Simulation.h"
#include <utility>

Simulation::Simulation(Graph graph, vector<Agent> agents) : mGraph(std::move(graph)), mAgents(std::move(agents)),
                                                            mCoalitions(vector<Coalition>{}), maxMandatesCoalition(0),
                                                            joinedMandates(0) {
    // Reserve enough memory for maximum amount of agents
    mAgents.reserve(mGraph.getNumVertices());

    // Initialize coalition for each agent
    for (unsigned int i = 0; i < mAgents.size(); i++) {
        Agent &agent = mAgents[i];
        agent.setCoalition(i);
        Coalition agentCoalition(agent.getId());

        // Add agent's party to its coalition
        Party &party = mGraph.getPartyById(agent.getPartyId());
        agentCoalition.addParty(party);

        // Update simulation fields
        joinedMandates += party.getMandates();
        maxMandatesCoalition = std::max(maxMandatesCoalition, agentCoalition.getMandates());

        mCoalitions.push_back(agentCoalition);
    }
}

void Simulation::step() {

    // Parties step: iterate each party and invoke "step"
    vector<Party> &parties = mGraph.getParties();
    for (unsigned int i = 0; i < parties.size(); i++) {
        Party &party = parties[i];
        if (party.getState() == CollectingOffers) {
            int partyTimer = party.getTimer();
            if (partyTimer != 0)
                party.setTimer(partyTimer == -1 ? 1 : partyTimer - 1);
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
    return maxMandatesCoalition > 60 || joinedMandates == 120;
}

Coalition &Simulation::getCoalition(int coalitionId) {
    return mCoalitions[coalitionId];
}

const Graph &Simulation::getGraph() const {
    return mGraph;
}

Graph &Simulation::getGraph() {
    return mGraph;
}

const vector<Agent> &Simulation::getAgents() const {
    return mAgents;
}

const Party &Simulation::getParty(int partyId) const {
    return mGraph.getParty(partyId);
}


void Simulation::cloneAgent(int agentId, int partyId) {
    Agent &agentToClone = mAgents[agentId];
    Agent toAdd(mAgents.size(), partyId, agentToClone.getSelectionPolicy()->clone());
    toAdd.setCoalition(agentToClone.getCoalitionId());
    mAgents.push_back(toAdd);
}

void Simulation::addJoinedMandates(int mandates) {
    joinedMandates += mandates;
}

void Simulation::setMaxMandates(int coalitionMandates) {
    maxMandatesCoalition = max(maxMandatesCoalition, coalitionMandates);
}

/// This method returns a "coalition" vector, where each element is a vector of party IDs in the coalition.
/// At the simulation initialization - the result will be [[agent0.partyId], [agent1.partyId], ...]
const vector<vector<int>> Simulation::getPartiesByCoalitions() const {
    vector<vector<int>> ans;
    for (const Coalition &coalition: mCoalitions)
        ans.push_back(coalition.getExistingParties());
    return ans;
}