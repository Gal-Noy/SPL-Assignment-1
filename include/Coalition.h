#pragma once

#include <set>
#include <vector>

class Agent;
class Party;

using std::set;
using std::vector;

class Coalition {
public:
    Coalition(int agentId);
    virtual ~Coalition() = default;// destructor
    Coalition(const Coalition &other); // copy constructor
    Coalition(Coalition &&other) noexcept ; // move constructor
    Coalition &operator=(const Coalition &other); // copy assignment operator
    Coalition &operator=(Coalition &&other) noexcept ; // move assignment operator

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

