#include <vector>
#include "Coalition.h"
#include "Party.h"

Coalition::Coalition(int agentId) : mAgentId(agentId), existingParties(vector<int>{}),
                                    offeredParties(vector<int>{}), mandates(0) {}

int Coalition::getAgentId() const {
    return mAgentId;
}

int Coalition::getMandates() const {
    return mandates;
}

void Coalition::addParty(Party &party) {
    existingParties.push_back(party.getId());
    mandates += party.getMandates();
}

void Coalition::offerParty(int partyId) {
    offeredParties.push_back(partyId);
}

const vector<int> &Coalition::getOfferedParties() const {
    return offeredParties;
}

const vector<int> &Coalition::getExistingParties() const {
    return existingParties;
}
