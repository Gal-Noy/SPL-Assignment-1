#include "Coalition.h"

Coalition::Coalition(Agent &agent, set<Party*> &_existingParties, int _mandates) :
mAgent(&agent),
existingParties(_existingParties),
availableParties(set<Party*>{}), //TODO: is there a need in "new" here?
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

set<Party*> &Coalition::getParties() {
    return existingParties;
}

void Coalition::addParty(Party &party, int mandates) {
    existingParties.insert(&party);
    addMandates(mandates);
    availableParties.erase(&party);
}

set<Party*> &Coalition::getAvailableParties() {
    return availableParties;
}

void Coalition::addAvailableParty(Party &party) {
    availableParties.insert(&party);
}