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

//    virtual ~Party(); // destructor
//    Party(const Party &other); // copy constructor
//    Party(Party &&other); // move constructor
//    Party &operator=(const Party &other); // copy assignment operator
//    Party &operator=(Party &&other); // move assignment operator

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
