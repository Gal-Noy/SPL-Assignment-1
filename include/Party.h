#pragma once
#include <string>
#include <vector>
#include "Coalition.h"

using std::string;
using std::vector;

class JoinPolicy;
class Simulation;

enum State
{
    Waiting,
    CollectingOffers,
    Joined
};

class Party
{
public:
    Party(int id, string name, int mandates, JoinPolicy *);

    State getState() const;
    void setState(State state);
    int getMandates() const;
    int getId() const;
    int getCooldown() const;
    void changeCooldown();
    void step(Simulation &s);
    const string &getName() const;
    void addOffer(Coalition &coalition);

private:
    int mId;
    string mName;
    int mMandates;
    JoinPolicy *mJoinPolicy;
    State mState;
    int cooldown;
    vector<Coalition&> offers;
};
