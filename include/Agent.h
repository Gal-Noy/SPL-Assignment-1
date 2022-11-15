#pragma once

#include <vector>
#include "Graph.h"
#include "SelectionPolicy.h";

class Agent
{
public:
    Agent(int agentId, int partyId, SelectionPolicy *selectionPolicy);

    int getId() const;
    int getPartyId() const;
    void step(Simulation &);

private:
    int mAgentId;
    int mPartyId;
    SelectionPolicy *mSelectionPolicy;
};
