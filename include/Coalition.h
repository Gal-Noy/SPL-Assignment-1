#pragma once

#include <set>

using std::set;

class Agent;

class Party;

class Coalition {
public:
    Coalition(Agent &agent, set<Party *> existingParties, int mandates);

    virtual ~Coalition();

    Coalition(const Coalition &other);

    Coalition &operator=(const Coalition &other);

    Coalition &operator=(Coalition &&other);

    friend bool operator>(const Coalition &c1, const Coalition &c2);

    const Agent &getAgent() const;

    int getMandates() const;

    void addMandates(int toAdd);

    set<Party *> getParties() const;

    void addParty(Party *party); //adds party to existing and removes from available
    set<Party *> getAvailableParties() const;

    void addAvailableParty(Party *party);

private:
    Agent &mAgent;
    set<Party *> existingParties;
    set<Party *> availableParties;
    int mandates{};
};