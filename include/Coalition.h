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
    Coalition(Agent *agent, vector<const Party *> existingParties);
    virtual ~Coalition(); // destructor
    Coalition(const Coalition &other); // copy constructor
    Coalition(Coalition &&other); // move constructor
    Coalition &operator=(const Coalition &other); // copy assignment operator
    Coalition &operator=(Coalition &&other); // move assignment operator

    friend bool operator>(const Coalition &c1, const Coalition &c2);

    const Agent &getAgent() const;

    int getMandates() const;

    void addParty(const Party *);

    const vector<const Party *> &getExistingParties() const;

    void offerParty(const Party &);

    const set<const Party *> &getOfferedParties() const;

private:
    Agent *mAgent;
    vector<const Party *> existingParties;
    set<const Party *> offeredParties;
    int mandates;
};

