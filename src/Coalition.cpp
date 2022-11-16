#include <vector>
#include "Coalition.h"

Coalition::Coalition(Agent &agent, vector<const Party *> _existingParties, int _mandates) :
mAgent(&agent),
existingParties(_existingParties),
availableParties(set<const Party*>{}), //TODO: is there a need in "new" here?
mandates(_mandates)
{
 // Implementation of constructor
}

//  TODO: rule of five
//    virtual ~Coalition();
//    Coalition(const Coalition &other);
//    Coalition &operator=(const Coalition &other);
//    Coalition &operator=(Coalition &&other);

bool operator>(const Coalition &c1, const Coalition &c2) {
    return c1.getMandates() > c2.getMandates();
}

const Agent &Coalition::getAgent() const {
    return *mAgent;
}

int Coalition::getMandates() const {
    return mandates;
}

void Coalition::addMandates(int toAdd) {
    mandates += toAdd;
}

vector<const Party*> &Coalition::getParties() { //TODO: maybe delete if never used
    return existingParties;
}

void Coalition::addParty(const Party &party, int partyMandates) {
    existingParties.push_back(&party);
    addMandates(partyMandates);
    availableParties.erase(&party);
}

set<const Party*> &Coalition::getAvailableParties() { //TODO: maybe delete if never used
    return availableParties;
}

void Coalition::addAvailableParty(const Party &party) {
    availableParties.insert(&party);
}