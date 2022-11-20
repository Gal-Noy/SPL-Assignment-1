#pragma once

#include <vector>

class Coalition;
class Simulation;

using std::vector;

class JoinPolicy {
public:
    virtual JoinPolicy *clone() const = 0;
    virtual int choose(vector<int> &, Simulation &) = 0;
    virtual ~JoinPolicy() = default;
};

class MandatesJoinPolicy : public JoinPolicy {
public:
    MandatesJoinPolicy *clone() const override;
    int choose(vector<int> &, Simulation &) override;
    ~MandatesJoinPolicy() override = default;
};

class LastOfferJoinPolicy : public JoinPolicy {
public:
    LastOfferJoinPolicy *clone() const override;
    int choose(vector<int> &, Simulation &) override;
    ~LastOfferJoinPolicy() override = default;
};