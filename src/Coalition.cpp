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

//Coalition::~Coalition() { // destructor
//    if (mAgent) delete mAgent;
//    for (const Party * party : existingParties){
//        delete party;
//    }
//    for (auto & party : existingParties){
//        delete party;
//    }
//}
//
//Agent::Agent(const Agent &other){ // copy constructor
//    mAgentId = other.mAgentId;
//    mPartyId = other.mPartyId;
//    mCoalition = new Coalition(*(other.mCoalition));
//    mSelectionPolicy = new SelectionPolicy(*(other.mSelectionPolicy));
//}
//
//Agent::Agent(Agent &&other){ // move constructor
//    mAgentId = other.mAgentId;
//    mPartyId = other.mPartyId;
//    mCoalition = other.mCoalition;
//    other.mCoalition = nullptr;
//    mSelectionPolicy = other.mSelectionPolicy;
//    other.mSelectionPolicy = nullptr;
//}
//
//Agent &Agent::operator=(const Agent &other) { // copy assignment operator
//    if (this != &other){
//        mAgentId = other.mAgentId;
//        mPartyId = other.mPartyId;
//        *mCoalition = *other.mCoalition;
//        *mSelectionPolicy = *other.mSelectionPolicy;
//    }
//    return *this;
//}
//
//Agent &Agent::operator=(Agent &&other){ // move assignment operator
//    mAgentId = other.mAgentId;
//    mPartyId = other.mPartyId;
//    if (mCoalition) delete mCoalition;
//    mCoalition = other.mCoalition;
//    other.mCoalition = nullptr;
//    if (mSelectionPolicy) delete mSelectionPolicy;
//    mSelectionPolicy = other.mSelectionPolicy;
//    other.mSelectionPolicy = nullptr;
//    return *this;
//}

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

