#pragma once
#include <string>
#include <vector>
#include "JoinPolicy.h"
#include "Coalition.h"


using std::string;
using std::vector;

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
//    virtual ~Party(); // destructor
//    Party(const Party &other); // copy constructor
//    Party(Party &&other); // move constructor
//    Party &operator=(const Party &other); // copy assignment operator
//    Party &operator=(Party &&other); // move assignment operator

    State getState() const;
    void setState(State state);
    int getMandates() const;
    void step(Simulation &s);
    const string &getName() const;

    int getId() const;
    void changeCooldown();
    void addOffer(Coalition &coalition);
    const vector<Coalition*> &getOffers() const;

private:
    int mId;
    string mName;
    int mMandates;
    JoinPolicy *mJoinPolicy;
    State mState;
    int cooldown;
    vector<Coalition*> offers;
};
