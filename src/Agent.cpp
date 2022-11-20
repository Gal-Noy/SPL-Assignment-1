#include <iostream>
#include <algorithm>
#include "Agent.h"

Agent::Agent(int agentId, int partyId, SelectionPolicy *selectionPolicy) : mAgentId(agentId), mPartyId(partyId),
                                                                           mCoalitionId(-1),
                                                                           mSelectionPolicy(selectionPolicy) {}
// destructor
Agent::~Agent() {
    if (mSelectionPolicy) delete mSelectionPolicy;
}

// copy constructor
Agent::Agent(const Agent &other) : mAgentId(other.mAgentId), mPartyId(other.mPartyId),
                                   mCoalitionId(other.mCoalitionId),
                                   mSelectionPolicy(other.mSelectionPolicy->clone()){}

// move constructor
Agent::Agent(Agent &&other) noexcept : mAgentId(other.mAgentId), mPartyId(other.mPartyId),
                              mCoalitionId(other.mCoalitionId),
                              mSelectionPolicy(other.mSelectionPolicy->clone()){}

// copy assignment operator
Agent &Agent::operator=(const Agent &other) {
    if (this != &other) {
        mAgentId = other.mAgentId;
        mPartyId = other.mPartyId;
        mCoalitionId = other.mCoalitionId;
        *mSelectionPolicy = *other.mSelectionPolicy;
    }
    return *this;
}

// move assignment operator
Agent &Agent::operator=(Agent &&other) noexcept {
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

    Graph &graph = sim.getGraph();
    Coalition &agentCoalition = sim.getCoalition(mCoalitionId);

    // Get available parties to select from
    vector<Party *> availableParties;

    // Find neighbors in state Waiting/CollectingOffers without active offer from agent's coalition
    for (int i = 0; i < graph.getNumVertices(); i++) {
        if (i != mPartyId) {
            Party &party = graph.getPartyById(i);
            const vector<int> &offeredParties = agentCoalition.getOfferedParties();
            if (graph.getEdgeWeight(mPartyId, i) != 0 && party.getState() != Joined &&
                find(offeredParties.begin(), offeredParties.end(), i) == offeredParties.end()) {
                availableParties.push_back(&party);
            }
        }
    }

    // Select party to offer from available parties
    if (!availableParties.empty()) {
        int partyToSelectId = mSelectionPolicy->select(availableParties, mPartyId, graph);
        Party *selectedParty = availableParties[partyToSelectId];

        // Offer party
        agentCoalition.offerParty(selectedParty->getId());
        selectedParty->addOffer(mCoalitionId);

        // Change state (if the party is offered for the first time)
        if (selectedParty->getState() == Waiting)
            selectedParty->setState(CollectingOffers);
    }
}