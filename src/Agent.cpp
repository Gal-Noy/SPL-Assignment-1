#include <iostream>
#include "Agent.h"

Agent::Agent(int agentId, int partyId, SelectionPolicy *selectionPolicy) : mAgentId(agentId), mPartyId(partyId),
                                                                           mCoalition(nullptr),
                                                                           mSelectionPolicy(selectionPolicy) {
}

Agent::~Agent() { // destructor
//    if (mCoalition) delete mCoalition;
    std::cout << "AAAAAAAAAAAAAAAAAAAAAAAAAA" << std::endl;
}

Agent::Agent(const Agent &other) { // copy constructor
    mAgentId = other.mAgentId;
    mPartyId = other.mPartyId;
    mCoalition = other.mCoalition;
//    mCoalition = new Coalition(*other.mCoalition);
    mSelectionPolicy = other.mSelectionPolicy;
}

Agent::Agent(Agent &&other) { // move constructor
    mAgentId = other.mAgentId;
    mPartyId = other.mPartyId;

    mCoalition = other.mCoalition;
    other.mCoalition = nullptr;

    mSelectionPolicy = other.mSelectionPolicy;
    other.mSelectionPolicy = nullptr;
}

Agent &Agent::operator=(const Agent &other) { // copy assignment operator
    if (this != &other) {
        mAgentId = other.mAgentId;
        mPartyId = other.mPartyId;

        *mCoalition = *other.mCoalition;
        *mSelectionPolicy = *other.mSelectionPolicy;
    }
    return *this;
}

Agent &Agent::operator=(Agent &&other) { // move assignment operator
    mAgentId = other.mAgentId;
    mPartyId = other.mPartyId;

    if (mCoalition) delete mCoalition;
    mCoalition = other.mCoalition;
    other.mCoalition = nullptr;

    if (mSelectionPolicy) delete mSelectionPolicy;
    mSelectionPolicy = other.mSelectionPolicy;
    other.mSelectionPolicy = nullptr;

    return *this;
}

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
    std::cout << "started step agent " << mAgentId << std::endl;
    vector<const Party *> availableParties;
    const Graph &graph = sim.getGraph();
    Coalition *agentCoalition = getCoalition();

//    /// Debug
//    std::cout << "agent id " << mAgentId << std::endl;
//    std::cout << "party id " << mPartyId << std::endl;
//    std::cout << "col id " << agentCoalition.getAgent().mAgentId << std::endl;

    // get availableParties
    for (int i = 0; i < graph.getNumVertices(); i++) {
        if (i != mPartyId) {
            const Party *party = &graph.getParty(i);
            const set<const Party *> &offeredParties = agentCoalition->getOfferedParties();
            if (graph.getEdgeWeight(mPartyId, i) != 0 && party->getState() != Joined &&
                offeredParties.find(party) == offeredParties.end()) {
                availableParties.push_back(party);
            }
        }
    }
    if (!availableParties.empty()) {
        int index = mSelectionPolicy->select(availableParties, mPartyId, graph);
        auto *selectedParty = const_cast<Party *>(availableParties[index]);
        agentCoalition->offerParty(selectedParty);
        selectedParty->addOffer(agentCoalition);
        if (selectedParty->getState() == Waiting)
            selectedParty->setState(CollectingOffers);
        std::cout << "agent " << mAgentId << " of coalition " << getCoalition()->getAgent().getId() << " offered party " << selectedParty->getId() << std::endl;
    }

    std::cout << "ended step agent " << mAgentId << std::endl;
}