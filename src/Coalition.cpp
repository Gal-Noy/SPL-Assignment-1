#include "Coalition.h"
#include <vector>

using std::vector;

Coalition::Coalition(Agent agent, vector<Party> _existingParties, int _mandates) :
mAgent(agent),
existingParties(_existingParties),
availableParties(vector<Party>{}),
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

const Agent Coalition::getAgent() const {
    return mAgent;
}

int Coalition::getMandates() const {
    return mandates;
}

void Coalition::addMandates(int toAdd) {
    mandates += toAdd;
}

vector<Party> Coalition::getParties() const {
    return existingParties;
}

void Coalition::addParty(Party party) {  //adds party to existing and removes from available
    existingParties.push_back(party);
    addMandates(party.getMandates());
    int id = party.getId();
    for (int i = 0; i < availableParties.size(); i++) {
        if (availableParties[i].getId() == id)
            availableParties.erase(availableParties.begin() + i); // TODO: must debug!!!
    }
}

vector<Party> Coalition::getAvailableParties() const {
    return availableParties;
}

void Coalition::addAvailableParty(Party party) {
    availableParties.push_back(party);
}