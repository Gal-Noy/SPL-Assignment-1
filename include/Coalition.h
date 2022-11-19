#pragma once

#include <set>
#include <vector>

//TODO: I believe includes and FD are done in here god dammit

class Agent;
class Party;

using std::set;
using std::vector;

class Coalition {
public:
    Coalition(Agent *agent, vector<Party *> existingParties);
    virtual ~Coalition(); // destructor
    Coalition(const Coalition &other); // copy constructor
    Coalition(Coalition &&other); // move constructor
    Coalition &operator=(const Coalition &other); // copy assignment operator
    Coalition &operator=(Coalition &&other); // move assignment operator

    Agent &getAgent();

    int getMandates() const;

    void addParty(Party &);

    void offerParty(const Party *);

    const set<const Party *> &getOfferedParties() const;

private:
    Agent *mAgent;
    vector<Party *> existingParties;
    set<const Party *> offeredParties;
    int mandates;
};

