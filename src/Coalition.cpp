#include <utility>
#include <vector>
#include <iostream>
#include "Coalition.h"
#include "Party.h"
#include "Agent.h"

Coalition::Coalition(int agentId, vector<int> _existingParties) :
        mAgentId(agentId),
        existingParties(std::move(_existingParties)),
        offeredParties(vector<int>{}), //
        mandates(0)
{
    // Implementation of constructor
}

Coalition::~Coalition() { // destructor

//    for (Party * party : existingParties){
//        delete party;
//    }
//    existingParties.clear();
//
//    for (const Party * party : offeredParties){
//        delete party;
//    }
//    offeredParties.clear();

    std::cout << "COALITION DESTRUCTOR ACTIVATED" << std::endl;
}

Coalition::Coalition(const Coalition &other){ // copy constructor
    mandates = other.mandates;
    mAgentId = other.mAgentId;
    existingParties = vector<int>(other.existingParties);
    offeredParties = vector<int>(other.offeredParties);
}

Coalition::Coalition(Coalition &&other){ // move constructor
    mandates = other.mandates;
    mAgentId = other.mAgentId;

    existingParties = std::move(other.existingParties);
////    for (const Party * party : existingParties){
////        delete party;
////    }
    offeredParties = std::move(other.offeredParties);
////    for (const Party * party : offeredParties){
////        delete party;
////    }
}

//Coalition &Coalition::operator=(const Coalition &other) { // copy assignment operator
//    if (this != &other){
//        mandates = other.mandates;
//        mAgentId = other.mAgentId;
//
//        existingParties = other.existingParties;
//        offeredParties = other.offeredParties;
//    }
//    return *this;
//}
//
//Coalition &Coalition::operator=(Coalition &&other){ // move assignment operator
//    mandates = other.mandates;
//    mAgentId = other.mAgentId;
//
//    existingParties = std::move(other.existingParties);
//    offeredParties = std::move(other.offeredParties);

//    for (const Party * party : existingParties){
//        delete party;
//    }
//    existingParties = other.existingParties;
//    for (const Party * party : offeredParties){
//        delete party;
//    }
//    offeredParties = other.offeredParties;

//    return *this;
//}

int Coalition::getAgentId() const{
    return mAgentId;
}

int Coalition::getMandates() const {
    return mandates;
}

void Coalition::addParty(Party &party) {
    existingParties.push_back(party.getId());
    mandates += party.getMandates();
    std::cout << "coalition " << mAgentId << " added party " << party.getId() << " and its mandates amount is " << mandates << std::endl;
}

void Coalition::offerParty(int partyId){
    offeredParties.push_back(partyId);
}
const vector<int> &Coalition::getOfferedParties() const{
    return offeredParties;
}
