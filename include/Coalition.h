#pragma once

#include <set>
#include <vector>

class Agent;
class Party;

using std::set;
using std::vector;

class Coalition {
public:
    explicit Coalition(int agentId);

    int getAgentId() const;
    int getMandates() const;
    void addParty(Party &);
    void offerParty(int);
    const vector<int> &getOfferedParties() const;
    const vector<int> &getExistingParties() const;

private:
    int mAgentId;
    vector<int> existingParties;
    vector<int> offeredParties;
    int mandates;
};

