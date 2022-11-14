#include "Agent.h"
#include "Party.h"
#include <set>

Coalition::Coalition(Agent &agent, set<Party *> _existingParties, int _mandates) : mAgent(agent),
                                                                                   existingParties(_existingParties),
                                                                                   availableParties(set<Party *>{}),
                                                                                   mandates(_mandates) {

}

Coalition::~Coalition() {
    // should Implement
}

Coalition::Coalition(const Coalition &other) : mAgent(other.mAgent), existingParties(other.existingParties),
                                               availableParties(other.availableParties) {

}

Coalition &Coalition::operator=(const Coalition &other) {

}

Coalition &Coalition::operator=(Coalition &&other) {

}

bool operator>(const Coalition &c1, const Coalition &c2) {
    return c1.getMandates() > c2.getMandates();
}

const Agent &Coalition::getAgent() const {
    return mAgent;
}

int Coalition::getMandates() const {
    return mandates;
}

void Coalition::addMandates(int toAdd) {
    mandates += toAdd;
}

set<Party *> Coalition::getParties() const {
    return existingParties;
}

void Coalition::addParty(Party *party) {
    existingParties.insert(party);
    addMandates(party->getMandates());
    availableParties.erase(party);
}

set<Party *> Coalition::getAvailableParties() const {
    return availableParties;
}

void Coalition::addAvailableParty(Party *party) {
    availableParties.insert(party);
}