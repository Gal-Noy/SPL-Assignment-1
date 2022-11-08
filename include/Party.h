#pragma once
#include <string>
#include <vector>

using std::string;

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
    Party();

    State getState() const;
    void setState(State state);
    int getMandates() const;
    int getId() const;
    int getCooldown() const;
    void changeCooldown();
    void step(Simulation &s);
    const string &getName() const;

private:
    int mId;
    string mName;
    int mMandates;
    JoinPolicy *mJoinPolicy;
    State mState;
    int cooldown = -1;
    vector<Agent> offers;
};
