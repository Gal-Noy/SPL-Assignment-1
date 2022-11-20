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
    virtual ~Party(); // destructor
    Party(const Party &other); // copy constructor
    Party(Party &&other) noexcept ; // move constructor
    Party &operator=(const Party &other); // copy assignment operator
    Party &operator=(Party &&other) noexcept ; // move assignment operator

    State getState() const;
    void setState(State state);
    int getMandates() const;
    void step(Simulation &s);
    const string &getName() const;

    int getId() const;
    void addOffer(int coalitionId);

private:
    int mId;
    string mName;
    int mMandates;
    JoinPolicy *mJoinPolicy;
    State mState;
    vector<int> offers;
};