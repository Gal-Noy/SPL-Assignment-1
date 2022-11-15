#pragma once
#include <string>
#include <vector>
#include "JoinPolicy.h"

using std::string;
using std::vector;

//class JoinPolicy; TODO: removed their FD, because we implemented a method inside this class which we use!
class Simulation;
class Coalition;

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
    // TODO: Rule of Five (I believe yes)

    State getState() const;
    void setState(State state);
    int getMandates() const;
    void step(Simulation &s);
    const string &getName() const;

    int getId() const;
    int getCooldown() const;
    void changeCooldown();
    void addOffer(Coalition &coalition);

private:
    int mId;
    string mName;
    int mMandates;
    JoinPolicy *mJoinPolicy;
    State mState;

    int cooldown;
    vector<Coalition*> offers;
};
