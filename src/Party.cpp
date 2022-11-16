#include "Party.h"

#include <utility>
#include "Simulation.h"

Party::Party(int id, string name, int mandates, JoinPolicy *jp) :
        mId(id),
        mName(std::move(name)),
        mMandates(mandates),
        mJoinPolicy(jp),
        mState(Waiting),
        cooldown(-1),
        offers(vector<Coalition *>{}) {
}

Party::~Party() { // destructor
    if (mJoinPolicy) delete mJoinPolicy;
    for (Coalition * coalition : offers){
        delete coalition;
    }
}

Party::Party(const Party &other) { // copy constructor
    mId = other.mId;
    mName = other.mName;
    mMandates = other.mMandates;
    cooldown = other.cooldown;
    mState = other.mState;
    mJoinPolicy = other.mJoinPolicy;
    offers = *new vector<Coalition *>(other.offers);
}

Party::Party(Party &&other) { // move constructor
    mId = other.mId;
    mName = other.mName;
    mMandates = other.mMandates;
    cooldown = other.cooldown;
    mState = other.mState;
    mJoinPolicy = other.mJoinPolicy;
    other.mJoinPolicy = nullptr;
    offers = other.offers;
    for (Coalition * coalition : offers){
        delete coalition;
    }
}

Party &Party::operator=(const Party &other) { // copy assignment operator
    if (this != &other) {
        mId = other.mId;
        mName = other.mName;
        mMandates = other.mMandates;
        cooldown = other.cooldown;
        mState = other.mState;
        *mJoinPolicy = *other.mJoinPolicy;
        offers = other.offers;
    }
    return *this;
}

Party &Party::operator=(Party &&other) { // move assignment operator
    mId = other.mId;
    mName = other.mName;
    mMandates = other.mMandates;
    cooldown = other.cooldown;
    mState = other.mState;
    if (mJoinPolicy) delete mJoinPolicy;
    mJoinPolicy = other.mJoinPolicy;
    other.mJoinPolicy = nullptr;
    for (Coalition * coalition : offers){
        delete coalition;
    }
    offers = other.offers;
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

void Party::changeCooldown() {
    if (cooldown < 0)
        cooldown = 2;
    else if (cooldown > 0)
        cooldown--;
}

void Party::step(Simulation &s) {
    if (getState() != CollectingOffers)
        return;

    if (cooldown > 0) {
        changeCooldown();
        return;
    }
    Coalition *toJoin = mJoinPolicy->choose(offers);
    const Party &self = *this;
    toJoin->addParty(self, this->getMandates());
    s.cloneAgent(toJoin->getAgent(), mId);

    setState(Joined);
}

void Party::addOffer(Coalition &coalition) {
    offers.push_back(&coalition);
}

const vector<Coalition *> &Party::getOffers() const {
    return offers;
}
