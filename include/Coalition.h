#pragma once

#include <vector>
#include "Party.h"

//TODO: I believe includes and FD are done in here god dammit

class Agent;

using std::vector;

class Coalition {
public:
    Coalition(Agent &agent, vector<Party*> &existingParties, int mandates);
//    virtual ~Coalition();
//    Coalition(const Coalition &other);
//    Coalition &operator=(const Coalition &other);
//    Coalition &operator=(Coalition &&other);

    friend bool operator>(const Coalition &c1, const Coalition &c2);

    const Agent &getAgent() const;
    int getMandates() const;
    void addMandates(int toAdd);
    vector<Party*> &getParties();
    void addParty(Party &party);
    vector<Party*> &getAvailableParties();
    void addAvailableParty(Party &party);

private:
    Agent *mAgent;
    vector<Party*> existingParties;
    vector<Party*> availableParties;
    int mandates;
};


