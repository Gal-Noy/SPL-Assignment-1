#pragma once

#include <vector>
#include "Graph.h"
#include "SelectionPolicy.h"
#include "Simulation.h"

class Agent {
public:
    Agent(int agentId, int partyId, SelectionPolicy *selectionPolicy);
    virtual ~Agent(); // destructor
    Agent(const Agent &other); // copy constructor
    Agent(Agent &&other); // move constructor
    Agent &operator=(const Agent &other); // copy assignment operator
    Agent &operator=(Agent &&other); // move assignment operator

    int getId() const;

    Coalition *getCoalition() const;

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