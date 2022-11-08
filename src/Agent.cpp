#include "Agent.h"
#include "Simulation.h"
#include "SelectionPolicy.h"
#include <iostream>

Agent::Agent(int agentId, int partyId, SelectionPolicy *selectionPolicy) : mAgentId(agentId), mPartyId(partyId), mSelectionPolicy(selectionPolicy)
{
    // You can change the implementation of the constructor, but not the signature!

}

int Agent::getId() const
{
    return mAgentId;
}

int Agent::getPartyId() const
{
    return mPartyId;
}

void Agent::step(Simulation &sim)
{
    // TODO: implement this method

    const Graph &graph = sim.getGraph();
    vector<Party> possibleParties;
    for (int i = 0; i < graph.getNumVertices(); i++){
        const Party party = graph.getParty(i);
        if (graph.getEdgeWeight(this->getPartyId(), i) != 0 && party.getState() != Joined){
            possibleParties.push_back(party);
        }
    }
    if (possibleParties.size() > 0){
        Party partyToSelect = this->mSelectionPolicy->select(graph, possibleParties, this->getPartyId());
        std::cout << "party is " << partyToSelect.getName() << std::endl;
    }

}


