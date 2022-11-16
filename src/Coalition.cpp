#include <utility>
#include <vector>
#include "Coalition.h"

Coalition::Coalition(Agent &agent, vector<const Party *> _existingParties, int _mandates) :
mAgent(&agent),
existingParties(std::move(_existingParties)),
offeredParties(set<const Party*>{}), //
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

void Coalition::addParty(const Party &party, int partyMandates) {
    existingParties.push_back(&party);
    addMandates(partyMandates);
}

void Coalition::offerParty(const Party &party){
    offeredParties.insert(&party);
}
const set<const Party*> &Coalition::getOfferedParties() const{
    return offeredParties;
}

