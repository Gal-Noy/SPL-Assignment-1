#pragma once
#include <set>

//TODO: I believe includes and FD are done in here god dammit

class Agent;
class Party;

using std::set;

class Coalition {
public:
    Coalition(Agent &agent, set<Party*> &existingParties, int mandates);
//    virtual ~Coalition();
//    Coalition(const Coalition &other);
//    Coalition &operator=(const Coalition &other);
//    Coalition &operator=(Coalition &&other);

    friend bool operator>(const Coalition &c1, const Coalition &c2);

    const Agent &getAgent() const;
    int getMandates() const;
    void addMandates(int toAdd);
    set<Party*> &getParties();
    void addParty(Party &party, int mandates);
    set<Party*> &getAvailableParties();
    void addAvailableParty(Party &party);

private:
    Agent *mAgent;
    set<Party*> existingParties;
    set<Party*> availableParties;
    int mandates;
};


