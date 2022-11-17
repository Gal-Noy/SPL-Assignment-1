#include <utility>
#include <vector>
#include "Coalition.h"
#include "Party.h"
#include "Agent.h"

Coalition::Coalition(Agent &agent, vector<const Party *> _existingParties, int _mandates) :
        mAgent(&agent),
        existingParties(std::move(_existingParties)),
        offeredParties(set<const Party*>{}), //
        mandates(_mandates)
{
    // Implementation of constructor
}

Coalition::~Coalition() { // destructor
    if (mAgent) delete mAgent;
    for (const Party * party : existingParties){
        delete party;
    }
    for (const Party * party : offeredParties){
        delete party;
    }
}

Coalition::Coalition(const Coalition &other){ // copy constructor
    mandates = other.mandates;
    mAgent = new Agent(*(other.mAgent));
    existingParties = *new vector<const Party *>(other.existingParties);
    offeredParties = *new set<const Party *>(other.offeredParties);
}

Coalition::Coalition(Coalition &&other){ // move constructor
    mandates = other.mandates;
    mAgent = other.mAgent;
    other.mAgent = nullptr;
    existingParties = other.existingParties;
    for (const Party * party : existingParties){
        delete party;
    }
    offeredParties = other.offeredParties;
    for (const Party * party : offeredParties){
        delete party;
    }
}

Coalition &Coalition::operator=(const Coalition &other) { // copy assignment operator
    if (this != &other){
        mandates = other.mandates;
        *mAgent = *other.mAgent;
        existingParties = other.existingParties;
        offeredParties = other.offeredParties;
    }
    return *this;
}

Coalition &Coalition::operator=(Coalition &&other){ // move assignment operator
    mandates = other.mandates;
    if (mAgent) delete mAgent;
    mAgent = other.mAgent;
    other.mAgent = nullptr;
    for (const Party * party : existingParties){
        delete party;
    }
    existingParties = other.existingParties;
    for (const Party * party : offeredParties){
        delete party;
    }
    offeredParties = other.offeredParties;
    return *this;
}

bool operator>(const Coalition &c1, const Coalition &c2) {
    return c1.getMandates() > c2.getMandates();
}

const Agent &Coalition::getAgent() const {
    return *mAgent;
}

int Coalition::getMandates() const {
    return mandates;
}

void Coalition::addParty(const Party &party, int partyMandates) {
    existingParties.push_back(&party);
    mandates += partyMandates;
}

void Coalition::offerParty(const Party &party){
    offeredParties.insert(&party);
}
const set<const Party*> &Coalition::getOfferedParties() const{
    return offeredParties;
}
