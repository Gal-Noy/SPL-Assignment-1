#include "Agent.h"
#include <iostream>

Agent::Agent(int agentId, int partyId, SelectionPolicy *selectionPolicy) : mAgentId(agentId), mPartyId(partyId),
                                                                           mCoalition(new Coalition(this,
                                                                                                    vector<const Party *>{})),
                                                                           mSelectionPolicy(selectionPolicy) {
}

//Agent::~Agent() { // destructor
//    if (mCoalition) delete mCoalition;
//    if (mSelectionPolicy) delete mSelectionPolicy;
//}
//
//Agent::Agent(const Agent &other) { // copy constructor
//    mAgentId = other.mAgentId;
//    mPartyId = other.mPartyId;
//    mCoalition = new Coalition(*(other.mCoalition));
//    mSelectionPolicy = other.mSelectionPolicy;
//}
//
//Agent::Agent(Agent &&other) { // move constructor
//    mAgentId = other.mAgentId;
//    mPartyId = other.mPartyId;
//    mCoalition = other.mCoalition;
//    other.mCoalition = nullptr;
//    mSelectionPolicy = other.mSelectionPolicy;
//    other.mSelectionPolicy = nullptr;
//}
//
//Agent &Agent::operator=(const Agent &other) { // copy assignment operator
//    if (this != &other) {
//        mAgentId = other.mAgentId;
//        mPartyId = other.mPartyId;
//        *mCoalition = *other.mCoalition;
//        *mSelectionPolicy = *other.mSelectionPolicy;
//    }
//    return *this;
//}
//
//Agent &Agent::operator=(Agent &&other) { // move assignment operator
//    mAgentId = other.mAgentId;
//    mPartyId = other.mPartyId;
//    if (mCoalition) delete mCoalition;
//    mCoalition = other.mCoalition;
//    other.mCoalition = nullptr;
//    if (mSelectionPolicy) delete mSelectionPolicy;
//    mSelectionPolicy = other.mSelectionPolicy;
//    other.mSelectionPolicy = nullptr;
//    return *this;
//}

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

SelectionPolicy *Agent::getSelectionPolicy() const {
    return mSelectionPolicy;
}

void Agent::step(Simulation &sim) {

    vector<Party *> availableParties;
    const Graph &graph = sim.getGraph();
    const Party &agentParty = graph.getParty(mPartyId);
    Coalition *agentCoalition = getCoalition();

    // get availableParties
    for (int i = 0; i < graph.getNumVertices(); i++) {
        auto &party = const_cast<Party &>(graph.getParty(i));
        const vector<Coalition *> &offers = party.getOffers();
        const set<const Party *> &offeredParties = agentCoalition->getOfferedParties();
        if (graph.getEdgeWeight(mPartyId, i) != 0 && party.getState() != Joined &&
            offeredParties.find(&party) != offeredParties.end()) {
            availableParties.push_back(&party);
        }
    }
    Party &selectedParty = mSelectionPolicy->select(availableParties, mPartyId, graph);
    agentCoalition->offerParty(selectedParty);
    selectedParty.addOffer(agentCoalition);
}