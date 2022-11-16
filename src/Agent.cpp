#include "Agent.h"

Agent::Agent(int agentId, int partyId, SelectionPolicy *selectionPolicy) : mAgentId(agentId), mPartyId(partyId),
                                                                           mSelectionPolicy(selectionPolicy) {
    // You can change the implementation of the constructor, but not the signature!
}

// TODO: Rule of Five ?

int Agent::getId() const {
    return mAgentId;
}

int Agent::getPartyId() const {
    return mPartyId;
}

Coalition *Agent::getCoalition() const {
    return mCoalition;
}

void Agent::setCoalition(Coalition *coalition) {
    mCoalition = coalition;
}

void Agent::step(Simulation &sim) {
    // TODO: Add Coalition field to agent
    // get availableParties
    // select party from availableParties according to policy
    // remove party from availableParties
    // add Offer to party

//    TODO: Implemented so far:
//    const Graph &graph = sim.getGraph();
//    vector<Party> possibleParties;
//    for (int i = 0; i < graph.getNumVertices(); i++) {
//        const Party party = graph.getParty(i);
//        if (graph.getEdgeWeight(this->getPartyId(), i) != 0 && party.getState() != Joined) {
//            possibleParties.push_back(party);
//        }
//    }
//    if (!possibleParties.empty()) {
//        Party partyToSelect = this->mSelectionPolicy->select(graph, possibleParties, this->getPartyId());
//        std::cout << "party is " << partyToSelect.getName() << std::endl;
//    }
}
