#include "Simulation.h"
#include "Party.h"
#include <iostream>
#include <utility>

Party::Party(int id, string name, int mandates, JoinPolicy *jp) : mId(id), mName(std::move(name)), mMandates(mandates),
                                                                  mJoinPolicy(jp), mState(Waiting),
                                                                  offers(vector<int>{}) {

}

Party::~Party() { // destructor
    if (mJoinPolicy) delete mJoinPolicy;

    // std:cout << "PARTY DESTRUCTOR ACTIVATED" << std::endl;
}

Party::Party(const Party &other) : mId(other.mId), mName(other.mName), mMandates(other.mMandates),
                                   mJoinPolicy(other.mJoinPolicy->clone()), mState(other.mState),
                                   offers(vector<int>(other.offers)) {}// copy constructor

Party::Party(Party &&other) noexcept : mId(other.mId), mName(std::move(other.mName)), mMandates(other.mMandates),
                              mJoinPolicy(other.mJoinPolicy->clone()), mState(other.mState),
                              offers(std::move(other.offers)) { // move constructor
    other.mJoinPolicy = nullptr;
}

Party &Party::operator=(const Party &other) { // copy assignment operator

    if (this != &other) {

        mId = other.mId;
        mName = other.mName;
        mMandates = other.mMandates;
        mState = other.mState;

        *mJoinPolicy = *other.mJoinPolicy;

        offers = vector<int>(other.offers);
    }
    return *this;
}

Party &Party::operator=(Party &&other) noexcept { // move assignment operator

    mId = other.mId;
    mName = std::move(other.mName);
    mMandates = other.mMandates;
    mState = other.mState;

    if (mJoinPolicy) delete mJoinPolicy;
    mJoinPolicy = other.mJoinPolicy;
    other.mJoinPolicy = nullptr;

    offers = std::move(other.offers);

    return *this;
}

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
    for (int col: offers) {
        std::cout << col << std::endl;
    }
    int coalitionToJoinId = offers[mJoinPolicy->choose(offers, s)];
    Coalition &toJoin = s.getCoalition(coalitionToJoinId);
    std::cout << "party " << mId << " chose coalition " << toJoin.getAgentId() << std::endl;
    toJoin.addParty(*this);
    s.cloneAgent(toJoin.getAgentId(), mId);
    setState(Joined);

    std::cout << "ended step party " << mId << std::endl;
}

void Party::addOffer(int coalitionId) {
    offers.push_back(coalitionId);
}