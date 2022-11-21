#include "Simulation.h"
#include "Party.h"

Party::Party(int id, string name, int mandates, JoinPolicy *jp) : mId(id), mName(std::move(name)), mMandates(mandates),
                                                                  mJoinPolicy(jp), mState(Waiting),
                                                                  offers(vector<int>{}) {}
// destructor
Party::~Party() {
    if (mJoinPolicy) delete mJoinPolicy;
}

// copy constructor
Party::Party(const Party &other) : mId(other.mId), mName(other.mName), mMandates(other.mMandates),
                                   mJoinPolicy(other.mJoinPolicy->clone()), mState(other.mState),
                                   offers(vector<int>(other.offers)) {}

// move constructor
Party::Party(Party &&other) noexcept : mId(other.mId), mName(std::move(other.mName)), mMandates(other.mMandates),
                              mJoinPolicy(other.mJoinPolicy->clone()), mState(other.mState),
                              offers(std::move(other.offers)) {}

// copy assignment operator
Party &Party::operator=(const Party &other) {
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

// move assignment operator
Party &Party::operator=(Party &&other) noexcept {
    mId = other.mId;
    mName = std::move(other.mName);
    mMandates = other.mMandates;
    mState = other.mState;
    offers = std::move(other.offers);

    if (mJoinPolicy) delete mJoinPolicy;
    mJoinPolicy = other.mJoinPolicy;
    other.mJoinPolicy = nullptr;

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

void Party::addOffer(int coalitionId) {
    offers.push_back(coalitionId);
}

void Party::step(Simulation &s) {

    // Choosing which coalition to join from offers according to policy
    int coalitionToJoinId = offers[mJoinPolicy->choose(offers, s)];
    Coalition &toJoin = s.getCoalition(coalitionToJoinId);

    // Join the chosen coalition & clone its agent
    toJoin.addParty(*this);
    s.cloneAgent(toJoin.getAgentId(), mId);

    setState(Joined);

    // Update simulation fields
    s.addJoinedMandates(this->getMandates());
    s.setMaxMandates(toJoin.getMandates());
}
