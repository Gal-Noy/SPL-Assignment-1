#pragma once

#include <vector>

class Coalition;
class Simulation;

using std::vector;

class JoinPolicy {
public:
    virtual int choose(vector<int> &, Simulation &) = 0;
    virtual ~JoinPolicy() = default;
};

class MandatesJoinPolicy : public JoinPolicy {
public:
    int choose(vector<int> &, Simulation &) override;
};

class LastOfferJoinPolicy : public JoinPolicy {
public:
    int choose(vector<int> &, Simulation &) override;
};