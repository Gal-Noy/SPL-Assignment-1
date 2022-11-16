#include "Agent.h"

Agent::Agent(int agentId, int partyId, SelectionPolicy *selectionPolicy) : mAgentId(agentId), mPartyId(partyId),
                                                                           mCoalition(nullptr),
                                                                           mSelectionPolicy(selectionPolicy) {
}

// TODO: Rule of Five ?

int Agent::getId() const {
    return mAgentId;
}

int Agent::getPartyId() const {
    return mPartyId;
}

Coalition &Agent::getCoalition() const {
    return *mCoalition;
}

void Agent::setCoalition(Coalition *coalition) {
    mCoalition = coalition;
}

SelectionPolicy *Agent::getSelectionPolicy() const {
    return mSelectionPolicy;
}

void Agent::step(Simulation &sim) {

    vector<Party *> availableParties;
    const Graph &graph = sim.getGraph();
    const Party &agentParty = graph.getParty(mPartyId);
    Coalition agentCoalition = getCoalition();

    // get availableParties
    for (int i = 0; i < graph.getNumVertices(); i++) {
        auto &party = const_cast<Party &>(graph.getParty(i));
        const vector<Coalition *> &offers = party.getOffers();
        const set<const Party *> &offeredParties = agentCoalition.getOfferedParties();
        if (graph.getEdgeWeight(mPartyId, i) != 0 && party.getState() != Joined &&
            offeredParties.find(&party) != offeredParties.end()) {
            availableParties.push_back(&party);
        }
    }
    Party &selectedParty = mSelectionPolicy->select(availableParties, mPartyId, graph);
    agentCoalition.offerParty(selectedParty);
    selectedParty.addOffer(agentCoalition);
}
