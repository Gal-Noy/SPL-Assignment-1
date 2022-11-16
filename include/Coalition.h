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
    Coalition(Agent &agent, vector<const Party *> existingParties, int mandates);
    virtual ~Coalition();
    Coalition(const Coalition &other);
    Coalition &operator=(const Coalition &other);
    Coalition &operator=(Coalition &&other);

    friend bool operator>(const Coalition &c1, const Coalition &c2);

    const Agent &getAgent() const;

    int getMandates() const;

    void addMandates(int toAdd);

    void addParty(const Party &, int mandates);

    void offerParty(const Party &);

    const set<const Party *> &getOfferedParties() const;

private:
    Agent *mAgent;
    vector<const Party *> existingParties;
    set<const Party *> offeredParties;
    int mandates;
};


