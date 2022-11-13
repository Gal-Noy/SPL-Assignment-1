#include "Party.h"

Party::Party(int id, string name, int mandates, JoinPolicy *jp) : mId(id), mName(name), mMandates(mandates), mJoinPolicy(jp), mState(Waiting) 
{
    // You can change the implementation of the constructor, but not the signature!
}

Party::Party(){}

State Party::getState() const
{
    return mState;
}

void Party::setState(State state)
{
    mState = state;
}

int Party::getMandates() const
{
    return mMandates;
}

const string & Party::getName() const
{
    return mName;
}

int Party::getId() const
{
    return mId;
}

int Party::getCooldown() const
{
    return cooldown;
}

void Party::changeCooldown(){
    if (cooldown < 0)
        cooldown = 3;
    else if (cooldown > 0)
        cooldown--;
}

void Party::step(Simulation &s)
{
    // TODO
    // check if status is collectionOffers
    // update timer
    // join to coalition according to policy & clone agent & add neighbors to availableParties
    // update status
}
