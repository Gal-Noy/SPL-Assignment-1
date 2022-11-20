#include <utility>
#include <vector>
#include <iostream>
#include "Coalition.h"
#include "Party.h"
#include "Agent.h"

Coalition::Coalition(int agentId, vector<int> _existingParties) : mAgentId(agentId),
                                                                  existingParties(std::move(_existingParties)),
                                                                  offeredParties(vector<int>{}), mandates(0) {}

Coalition::~Coalition() {} // destructor

Coalition::Coalition(const Coalition &other) : mAgentId(other.mAgentId),
                                               existingParties(vector<int>(other.existingParties)),
                                               offeredParties(vector<int>(other.offeredParties)), mandates(other.mandates){} // copy constructor


Coalition::Coalition(Coalition &&other) : mAgentId(other.mAgentId),
                                          existingParties(std::move(other.existingParties)),
                                          offeredParties(std::move(other.offeredParties)), mandates(other.mandates){} // move constructor

Coalition &Coalition::operator=(const Coalition &other) { // copy assignment operator
    if (this != &other){
        mandates = other.mandates;
        mAgentId = other.mAgentId;
        existingParties = vector<int>(other.existingParties);
        offeredParties = vector<int>(other.offeredParties);
    }
    return *this;
}

Coalition &Coalition::operator=(Coalition &&other){ // move assignment operator
    mandates = other.mandates;
    mAgentId = other.mAgentId;
    existingParties = std::move(other.existingParties);
    offeredParties = std::move(other.offeredParties);
    return *this;
}

int Coalition::getAgentId() const {
    return mAgentId;
}

int Coalition::getMandates() const {
    return mandates;
}

void Coalition::addParty(Party &party) {
    existingParties.push_back(party.getId());
    mandates += party.getMandates();
    std::cout << "coalition " << mAgentId << " added party " << party.getId() << " and its mandates amount is "
              << mandates << std::endl;
}

void Coalition::offerParty(int partyId) {
    offeredParties.push_back(partyId);
}

const vector<int> &Coalition::getOfferedParties() const {
    return offeredParties;
}
