#pragma once

#include <vector>
#include "Graph.h"
#include "SelectionPolicy.h"
#include "Simulation.h"

class Agent {
public:
    Agent(int agentId, int partyId, SelectionPolicy *selectionPolicy);

    int getId() const;

    Coalition *getCoalition() const;

    void setCoalition(Coalition *);

    int getPartyId() const;

    void step(Simulation &);

private:
    int mAgentId;
    int mPartyId;
    Coalition *mCoalition;
    SelectionPolicy *mSelectionPolicy;
};
