#include <iostream>
#include "Agent.h"

Agent::Agent(int agentId, int partyId, SelectionPolicy *selectionPolicy) : mAgentId(agentId), mPartyId(partyId),
                                                                           mCoalitionId(-1),
                                                                           mSelectionPolicy(selectionPolicy) {
}

Agent::~Agent() { // destructor
//    if (mCoalition) delete mCoalition;
    std::cout << "AAAAAAAAAAAAAAAAAAAAAAAAAA" << std::endl;
}

Agent::Agent(const Agent &other) { // copy constructor
    mAgentId = other.mAgentId;
    mPartyId = other.mPartyId;
    mCoalitionId = other.mCoalitionId;
//    mCoalition = new Coalition(*other.mCoalition);
    mSelectionPolicy = other.mSelectionPolicy;
}

Agent::Agent(Agent &&other) { // move constructor
    mAgentId = other.mAgentId;
    mPartyId = other.mPartyId;
    mCoalitionId = other.mCoalitionId;

    mSelectionPolicy = other.mSelectionPolicy;
    other.mSelectionPolicy = nullptr;
}

Agent &Agent::operator=(const Agent &other) { // copy assignment operator
    if (this != &other) {
        mAgentId = other.mAgentId;
        mPartyId = other.mPartyId;
        mCoalitionId = other.mCoalitionId;
        *mSelectionPolicy = *other.mSelectionPolicy;
    }
    return *this;
}

Agent &Agent::operator=(Agent &&other) { // move assignment operator
    mAgentId = other.mAgentId;
    mPartyId = other.mPartyId;
    mCoalitionId = other.mCoalitionId;

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

int Agent::getCoalitionId() const {
    return mCoalitionId;
}

void Agent::setCoalition(int coalitionId) {
    mCoalitionId = coalitionId;
}

SelectionPolicy *Agent::getSelectionPolicy() const {
    return mSelectionPolicy;
}

void Agent::step(Simulation &sim) {
    std::cout << "started step agent " << mAgentId << std::endl;
    vector<const Party *> availableParties;
    const Graph &graph = sim.getGraph();
    Coalition &agentCoalition = const_cast<Coalition &>(sim.getCoalition(mCoalitionId));

//    /// Debug
//    std::cout << "agent id " << mAgentId << std::endl;
//    std::cout << "party id " << mPartyId << std::endl;
//    std::cout << "col id " << agentCoalition.getAgent().mAgentId << std::endl;

    // get availableParties
    for (int i = 0; i < graph.getNumVertices(); i++) {
        if (i != mPartyId) {
            const Party &party = graph.getParty(i);
            const set<const Party *> &offeredParties = agentCoalition.getOfferedParties();
            if (graph.getEdgeWeight(mPartyId, i) != 0 && party.getState() != Joined &&
                offeredParties.find(&party) == offeredParties.end()) {
                availableParties.push_back(&party);
            }
        }
    }
    if (!availableParties.empty()) {
        int index = mSelectionPolicy->select(availableParties, mPartyId, graph);
        auto *selectedParty = const_cast<Party *>(availableParties[index]);
        agentCoalition.offerParty(selectedParty);
        selectedParty->addOffer(&agentCoalition);
        if (selectedParty->getState() == Waiting)
            selectedParty->setState(CollectingOffers);
        std::cout << "agent " << mAgentId << " of coalition " << sim.getCoalition(mCoalitionId).getAgentId() << " offered party " << selectedParty->getId() << std::endl;
    }

    std::cout << "ended step agent " << mAgentId << std::endl;
}