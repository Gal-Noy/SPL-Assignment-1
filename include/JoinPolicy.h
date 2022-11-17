#pragma once

#include <vector>

class Coalition;

using std::vector;

//TODO: IMPLEMENT DESTRUCTOR

class JoinPolicy {
public:
    virtual Coalition *choose(vector<Coalition *> &offers) = 0;
};

class MandatesJoinPolicy : public JoinPolicy {
public:
    Coalition *choose(vector<Coalition *> &offers) override;
};

class LastOfferJoinPolicy : public JoinPolicy {
public:
    Coalition *choose(vector<Coalition *> &offers) override;
};