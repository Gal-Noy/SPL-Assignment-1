#include "Simulation.h"
#include "Party.h"
#include <iostream>
#include <utility>

Party::Party(int id, string name, int mandates, JoinPolicy *jp) :
        mId(id),
        mName(std::move(name)),
        mMandates(mandates),
        mJoinPolicy(jp),
        mState(Waiting),
        offers(vector<Coalition *>{}) {
}

//Party::~Party() { // destructor
//    if (mJoinPolicy) delete mJoinPolicy;
//    for (Coalition * coalition : offers){
//        delete coalition;
//    }
//}
//
//Party::Party(const Party &other) { // copy constructor
//    mId = other.mId;
//    mName = other.mName;
//    mMandates = other.mMandates;
//    cooldown = other.cooldown;
//    mState = other.mState;
//    mJoinPolicy = other.mJoinPolicy;
//    offers = *new vector<Coalition *>(other.offers);
//}
//
//Party::Party(Party &&other) { // move constructor
//    mId = other.mId;
//    mName = other.mName;
//    mMandates = other.mMandates;
//    cooldown = other.cooldown;
//    mState = other.mState;
//    mJoinPolicy = other.mJoinPolicy;
//    other.mJoinPolicy = nullptr;
//    offers = other.offers;
//    for (Coalition * coalition : offers){
//        delete coalition;
//    }
//}
//
//Party &Party::operator=(const Party &other) { // copy assignment operator
//    if (this != &other) {
//        mId = other.mId;
//        mName = other.mName;
//        mMandates = other.mMandates;
//        cooldown = other.cooldown;
//        mState = other.mState;
//        *mJoinPolicy = *other.mJoinPolicy;
//        offers = other.offers;
//    }
//    return *this;
//}
//
//Party &Party::operator=(Party &&other) { // move assignment operator
//    mId = other.mId;
//    mName = other.mName;
//    mMandates = other.mMandates;
//    cooldown = other.cooldown;
//    mState = other.mState;
//    if (mJoinPolicy) delete mJoinPolicy;
//    mJoinPolicy = other.mJoinPolicy;
//    other.mJoinPolicy = nullptr;
//    for (Coalition * coalition : offers){
//        delete coalition;
//    }
//    offers = other.offers;
//    return *this;
//}

State Party::getState() const {
    return mState;
}

void Party::setState(State state) {
    mState = state;
}

int Party::getMandates() const {
    return mMandates;
}

const string &Party::getName() const {
    return mName;
}

int Party::getId() const {
    return mId;
}

void Party::step(Simulation &s) {
    std::cout << "started step party " << mId << " with offers amount of " << offers.size() << std::endl;

    /// Debug
    std::cout << "party's offers are:" << std::endl;
    for (Coalition * col : offers){
        std::cout << col->getAgent()->getId() << std::endl;
    }

    Coalition *toJoin = offers[mJoinPolicy->choose(offers)];
    std::cout << "party " << mId << " chose coalition " << toJoin->getAgent()->getId() << std::endl;
    toJoin->addParty(this);
    s.cloneAgent(const_cast<Agent *>(toJoin->getAgent()), mId);
    setState(Joined);

    std::cout << "ended step party " << mId << std::endl;
}

void Party::addOffer(Coalition *coalition) {
    offers.push_back(coalition);
}

const vector<Coalition *> &Party::getOffers() const {
    return offers;
}