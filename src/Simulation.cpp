#include "Simulation.h"

#include <utility>

Simulation::Simulation(Graph graph, vector<Agent> agents) : mGraph(std::move(graph)), mAgents(agents) {

    for (Agent agent: agents) {
        int mandates = getParty(agent.getPartyId()).getMandates();
        const Party *party = &getParty(agent.getPartyId());
        agent.setCoalition(new Coalition(agent, vector<const Party *>{}, mandates));
<<<<<<< HEAD
        Coalition &coalition = agent.getCoalition();
        coalition.addParty(const_cast<Party *>(party));
=======
        coalition.addParty(party, mandates);
>>>>>>> parent of d3f5035... success
    }
}

void Simulation::step() {
    const Graph &graph = getGraph();
    // 1. parties-step: parties that can answer offers, answer
    for (int i = 0; i < graph.getNumVertices(); i++) {
        Party party = graph.getParty(i);
        party.step(*this);
    }

    // 2. agents-step: select party to offer and offer
    for (Agent agent: mAgents) {
        agent.step(*this);
    }
}

bool Simulation::shouldTerminate() const {
    // should terminate when any coalition reaches 61 mandates or all parties are in state joined
    //TODO:
    // check coalitions and return true if mandates >= 61
    vector<vector<int>> politicalMap = getPartiesByCoalitions();
    int mandates = 0;
    for (const vector<int> &coalition: politicalMap) {
        for (int partyId: coalition)
            mandates += getParty(partyId).getMandates();

        if (mandates > 60) return true;
        mandates = 0;
    }

    // check parties and count waiting/collecting offers and return == 0
    for (int i = 0; i < getGraph().getNumVertices(); i++) {
        Party party = getParty(i);
        if (party.getState() != Joined) return false;
    }

    return true;
}

const Graph &Simulation::getGraph() const {
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
    std::map<Coalition*, vector<int>> map;
    for (Agent agent: getAgents()) {
        if (map.find(&agent.getCoalition()) == map.end())
            map[&agent.getCoalition()] = vector<int>();
        map[&agent.getCoalition()].push_back(agent.getPartyId());
    }

    vector<vector<int>> ans;
    for (const auto &coalitionVector: map)
        ans.push_back(coalitionVector.second);
    return ans;
}

void Simulation::cloneAgent(const Agent &agent, int partyId) {
    auto *toAdd = new Agent((int) mAgents.size(), partyId, agent.getSelectionPolicy());
    toAdd->setCoalition(&agent.getCoalition());
    mAgents.push_back(*toAdd);
}
