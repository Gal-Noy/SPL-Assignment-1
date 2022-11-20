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
    Coalition(int agentId, vector<int> existingParties);
    virtual ~Coalition(); // destructor
    Coalition(const Coalition &other); // copy constructor
    Coalition(Coalition &&other); // move constructor
    Coalition &operator=(const Coalition &other); // copy assignment operator
    Coalition &operator=(Coalition &&other); // move assignment operator

    int getAgentId() const;

    int getMandates() const;

    void addParty(Party &);

    void offerParty(int partyId);

    const vector<int> &getOfferedParties() const;

private:
    int mAgentId;
    vector<int> existingParties;
    vector<int> offeredParties;
    int mandates;
};

