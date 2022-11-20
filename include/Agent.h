#pragma once

#include <vector>
#include "Graph.h"
#include "SelectionPolicy.h"
#include "Simulation.h"

class Agent {
public:
    Agent(int agentId, int partyId, SelectionPolicy *selectionPolicy);

    virtual ~Agent(); // destructor
    Agent(const Agent &); // copy constructor
    Agent(Agent &&) noexcept ; // move constructor
    Agent &operator=(const Agent &); // copy assignment operator
    Agent &operator=(Agent &&) noexcept ; // move assignment operator

    int getId() const;

    int getCoalitionId() const;

    void setCoalition(int coalitionId);

    int getPartyId() const;

    void step(Simulation &);

    SelectionPolicy *getSelectionPolicy() const;

private:
    int mAgentId;
    int mPartyId;
    int mCoalitionId;
    SelectionPolicy *mSelectionPolicy;
};