#pragma once

#include <vector>
#include "Graph.h"

class SelectionPolicy;

class Agent
{
public:
    Agent(int agentId, int partyId, SelectionPolicy *selectionPolicy);

    int getPartyId() const;
    int getId() const;
    int getCoalition() const;
    void setCoalition(int);
    void step(Simulation &);

private:
    int mAgentId;
    int mPartyId;
    int coalition;
    SelectionPolicy *mSelectionPolicy;
};
