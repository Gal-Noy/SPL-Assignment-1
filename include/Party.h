#pragma once

#include <string>
#include <vector>
#include "JoinPolicy.h"
#include "Coalition.h"

using std::string;
using std::vector;

class Simulation;

enum State {
    Waiting,
    CollectingOffers,
    Joined
};

class Party {
public:
    Party(int id, string name, int mandates, JoinPolicy *);

    // Rule of Five
    virtual ~Party(); // destructor
    Party(const Party &); // copy constructor
    Party(Party &&) noexcept; // move constructor
    Party &operator=(const Party &); // copy assignment operator
    Party &operator=(Party &&) noexcept; // move assignment operator

    State getState() const;
    void setState(State state);
    int getMandates() const;
    void step(Simulation &s);
    const string &getName() const;
    int getId() const;
    void addOffer(int);
    int getTimer() const;
    void setTimer(int val);

private:
    int mId;
    string mName;
    int mMandates;
    int timer;
    JoinPolicy *mJoinPolicy;
    State mState;
    vector<int> offers;
};