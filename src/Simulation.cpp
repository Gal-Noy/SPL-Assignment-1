#include "Simulation.h"
#include <iostream> // to remove
#include <utility>

Simulation::Simulation(Graph graph, vector<Agent> agents) : mGraph(std::move(graph)), mAgents(std::move(agents)),
                                                            mParties(map<int, int>{}) {
    mAgents.reserve(mGraph.getNumVertices());

    for (Agent &agent: mAgents) {
        Coalition *agentCoalition = new Coalition(agent.getId(), vector<Party *>{});
        agent.setCoalition(agentCoalition);
        auto &party = const_cast<Party &>(getParty(agent.getPartyId()));
        agentCoalition->addParty(party);
    }
    vector<Party> &parties = mGraph.getParties();
    for (int i = 0; i < parties.size(); i++)
        mParties[i] = -1;

    for (Agent &agent: mAgents) {
        std::cout << "agent is " << &agent << std::endl;
        std::cout << "col is " << agent.getCoalition() << std::endl;
        std::cout << "party is " << &(getParty(agent.getPartyId())) << std::endl;
        std::cout << "coalition of agent number " << agent.getCoalition()->getAgentId() << " with party number "
                  << agent.getCoalition()->getAgentId() << " with "
                  << agent.getCoalition()->getMandates() << " mandates" << std::endl; // to remove
    }
}

void Simulation::step() {

    // 1. parties-step: parties that can answer offers, answer
    vector<Party> &parties = mGraph.getParties();
    for (int i = 0; i < parties.size(); i++){
        Party *party = &parties[i];
        if (party->getState() == CollectingOffers) {
            std::cout << "party " << party->getId() << " cd is " << mParties[i] << std::endl;
            if (mParties[i] != 0) {
                if (mParties[i] == -1)
                    mParties[i] = 1;
                else
                    mParties[i]--;
                std::cout << "party " << party->getId() << " timer set to " << mParties[i] << std::endl;
            } else
                party->step(*this);
        }
    }

    // 2. agents-step: select party to offer and offer
    for (Agent &agent: mAgents) {
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
        if (mandates > 60) {
            return true;
        }
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
    map<Coalition *, vector<int>> map;
    for (const Agent &agent: mAgents) {
        Coalition *agentCoalition = agent.getCoalition();
        if (map.find(agentCoalition) == map.end())
            map[agentCoalition] = vector<int>();
        map[agentCoalition].push_back(agent.getPartyId());
    }

    // Create output vector by map keys and values
    vector<vector<int>> ans;
    for (const auto &coalitionVector: map)
        ans.push_back(coalitionVector.second);

//    /// Debug:
//    std::cout << "list of coalitions now:" << std::endl; // to remove
//    for (int i = 0; i < ans.size(); i++){
//        vector<int> col = ans[i];
//        std::cout << "coalition number - " << i << std::endl; // to remove
//        for (int j : col){
//            std::cout << "party number - " << j << std::endl; // to remove
//        }
//    }
    return ans;
}

void Simulation::cloneAgent(int agentId, int partyId) {
    Agent &agentToClone = mAgents[agentId];
    Agent toAdd((int) mAgents.size(), partyId, agentToClone.getSelectionPolicy());
    toAdd.setCoalition(agentToClone.getCoalition());
    mAgents.push_back(toAdd);

    std::cout << "a new agent is added of id " << toAdd.getId() << ", with coalition "
              << toAdd.getCoalition()->getAgentId() << " and with party " << toAdd.getPartyId() << std::endl;

    //Debug::
    std::cout << "checking after clone:" << std::endl;
    for (Agent &agent : mAgents)
        std::cout << "agent " << agent.getId() << " is of col " << agent.getCoalition()->getAgentId() << std::endl;

}