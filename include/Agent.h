#pragma once

#include <vector>
#include "Graph.h"
#include "SelectionPolicy.h"
#include "Simulation.h"

class Agent {
public:
    Agent(int agentId, int partyId, SelectionPolicy *selectionPolicy);
    virtual ~Agent();
    Agent(const Agent &other);
    Agent(Agent &&other);
    Agent &operator=(const Agent &other);
    Agent &operator=(Agent &&other);

    int getId() const;

    Coalition &getCoalition() const;

    void setCoalition(Coalition *);

    int getPartyId() const;

    void step(Simulation &);

    SelectionPolicy *getSelectionPolicy() const;

private:
    int mAgentId;
    int mPartyId;
    Coalition *mCoalition;
    SelectionPolicy *mSelectionPolicy;
};
