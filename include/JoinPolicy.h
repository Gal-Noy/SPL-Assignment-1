#pragma once

#include <vector>

class Coalition;

using std::vector;

class JoinPolicy {
public:
    virtual int choose(vector<Coalition *> &offers) = 0;
    virtual ~JoinPolicy() = default;
};

class MandatesJoinPolicy : public JoinPolicy {
public:
    int choose(vector<Coalition *> &offers) override;
};

class LastOfferJoinPolicy : public JoinPolicy {
public:
    int choose(vector<Coalition *> &offers) override;
};