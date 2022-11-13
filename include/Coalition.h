#pragma once
#include "Party.h"
#include "Agent.h"
#include <set>

using std::set;

class Coalition
{
public:
    Coalition(Agent &agent, set<Party&> existingParties, int mandates);
    const Agent& getAgent() const;
    int getMandates() const;
    void addMandates(int toAdd);
    set<Party&> getParties() const;
    void addParty(Party &party); //adds party to existing and removes from available
    set<Party&> getAvailableParties() const;
    void addAvailableParty(Party &party);

private:
    Agent &mAgent;
    set<Party&> existingParties;
    set<Party&> availableParties;
    int mandates;
};