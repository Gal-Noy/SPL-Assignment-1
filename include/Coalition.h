#pragma once
#include "Party.h"
#include "Agent.h"
#include <vector>

using std::vector;

class Coalition
{
public:
    Coalition(vector<Agent> agent, vector<Party> existingParties, int mandates);
    vector<Agent> getAgents();
    void cloneAgent(Agent agent, Party party);
    int getMandates() const;
    void addMandates(int toAdd);
    vector<Party> getParties();
    void addParty(Party party); //adds party to existing and removes from available
    vector<Party> getAvailableParties();
    void addAvailableParty(Party party);

private:
    vector<Agent> agents;
    vector<Party> existingParties, availableParties;
    int mandates;
};