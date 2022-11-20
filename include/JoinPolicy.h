#pragma once

#include <vector>

class Coalition;
class Simulation;

using std::vector;

class JoinPolicy {
public:
    virtual JoinPolicy* clone() const = 0;
    virtual int choose(vector<int> &, Simulation &) = 0;
    virtual ~JoinPolicy() = default;
};

class MandatesJoinPolicy : public JoinPolicy {
public:
    virtual MandatesJoinPolicy* clone() const override;
    int choose(vector<int> &, Simulation &) override;
};

class LastOfferJoinPolicy : public JoinPolicy {
public:
    virtual LastOfferJoinPolicy* clone() const override;
    int choose(vector<int> &, Simulation &) override;
};