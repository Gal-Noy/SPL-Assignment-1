#include "Simulation.h"
#include <iostream> // to remove

Simulation::Simulation(Graph graph, vector<Agent> agents) : mGraph(std::move(graph)), mAgents(agents) {

    for (Agent &agent: agents) {
        int mandates = getParty(agent.getPartyId()).getMandates();
        const Party *party = &getParty(agent.getPartyId());
        agent.setCoalition(new Coalition(agent, vector<const Party *>{}, mandates));
        Coalition &coalition = agent.getCoalition();
        coalition.addParty(const_cast<Party *>(party));
        std::cout << "coalition of agent number " << coalition.getAgent().getId() << " with party number " << coalition.getAgent().getPartyId()<< " with "
                  << coalition.getMandates() << " mandates" << std::endl; // to remove
    }

    for (Agent &agent : agents){
        std::cout << "agent is " << &agent << std::endl;
        std::cout << "col is " << &(agent.getCoalition()) << std::endl;
        std::cout << "party is " << &(getParty(agent.getPartyId())) << std::endl;
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

    // check coalitions and return true if mandates >= 61
    vector<vector<int>> politicalMap = getPartiesByCoalitions();
    int mandates = 0;
    for (const vector<int> &coalition: politicalMap) {
        for (int partyId: coalition)
            mandates += getParty(partyId).getMandates();
        if (mandates > 60) return true;
        mandates = 0;
    }

    // check parties and check if there's a party without a coalition (state waiting/collecting offers)
    for (int i = 0; i < getGraph().getNumVertices(); i++) {
        const Party &party = getParty(i);
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

    // Create a table to map each party to its coalition
    std::map<Coalition *, vector<int>> map;
    std::cout << "..." << std::endl;
    for (const Agent &agent: getAgents()) {
        std::cout << "agent is " << &agent << std::endl;
        std::cout << "col is " << &(agent.getCoalition()) << std::endl;
        std::cout << "party is " << &(getParty(agent.getPartyId())) << std::endl;

        Coalition *agentCoalition = &agent.getCoalition();
//        std::cout << "agent number " << agent.getId() << std::endl; // to remove
        if (map.find(agentCoalition) == map.end())
            map[agentCoalition] = vector<int>();
        map[agentCoalition].push_back(agent.getPartyId());
    }

    // Create output vector by map keys and values
    vector<vector<int>> ans;
    for (const auto &coalitionVector: map)
        ans.push_back(coalitionVector.second);
    std::cout << "list of coalitions now:" << std::endl; // to remove
    for (int i = 0; i < ans.size(); i++){
        vector<int> col = ans[i];
        std::cout << "coalition number - " << i << std::endl; // to remove
        for (int j : col){
            std::cout << "party number - " << j << std::endl; // to remove
        }
    }
    return ans;
}

void Simulation::cloneAgent(const Agent &agent, int partyId) {
    auto *toAdd = new Agent((int) mAgents.size(), partyId, agent.getSelectionPolicy());
    toAdd->setCoalition(&agent.getCoalition());
    mAgents.push_back(*toAdd);
}