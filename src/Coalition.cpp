#include <utility>
#include <vector>
#include <iostream>
#include "Coalition.h"
#include "Party.h"
#include "Agent.h"

Coalition::Coalition(Agent *agent, vector<const Party *> _existingParties) :
        mAgent(agent),
        existingParties(std::move(_existingParties)),
        offeredParties(set<const Party*>{}), //
        mandates(0)
{
    // Implementation of constructor
}

Coalition::~Coalition() { // destructor
    if (mAgent) delete mAgent;

    for (const Party * party : existingParties){
        delete party;
    }
    existingParties.clear();

    for (const Party * party : offeredParties){
        delete party;
    }
    offeredParties.clear();
}

Coalition::Coalition(const Coalition &other){ // copy constructor
    mandates = other.mandates;
    mAgent = new Agent(*other.mAgent);
    existingParties = vector<const Party *>(other.existingParties);
    offeredParties = set<const Party *>(other.offeredParties);
}

Coalition::Coalition(Coalition &&other){ // move constructor
    mandates = other.mandates;

    mAgent = other.mAgent;
    other.mAgent = nullptr;

    existingParties = std::move(other.existingParties);
//    for (const Party * party : existingParties){
//        delete party;
//    }
    offeredParties = std::move(other.offeredParties);
//    for (const Party * party : offeredParties){
//        delete party;
//    }
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

    existingParties = std::move(other.existingParties);
    offeredParties = std::move(other.offeredParties);

//    for (const Party * party : existingParties){
//        delete party;
//    }
//    existingParties = other.existingParties;
//    for (const Party * party : offeredParties){
//        delete party;
//    }
//    offeredParties = other.offeredParties;

    return *this;
}

Agent *Coalition::getAgent(){
    return mAgent;
}

int Coalition::getMandates() const {
    return mandates;
}

void Coalition::addParty(const Party *party) {
    existingParties.push_back(party);
    mandates += party->getMandates();
    std::cout << "coalition " << getAgent()->getId() << " added party " << party->getId() << " and its mandates amount is " << mandates << std::endl;
}

const vector<const Party *> &Coalition::getExistingParties() const{
    return existingParties;
}

void Coalition::offerParty(const Party *party){
    offeredParties.insert(party);
}
const set<const Party*> &Coalition::getOfferedParties() const{
    return offeredParties;
}
