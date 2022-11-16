#pragma once

#include <vector>

class Coalition;

using std::vector;

class JoinPolicy {
public:
    virtual Coalition *choose(vector<Coalition *> &offers) = 0;
};

class MandatesJoinPolicy : public JoinPolicy {
public:
    virtual Coalition *choose(vector<Coalition *> &offers);
};

class LastOfferJoinPolicy : public JoinPolicy {
public:
    virtual Coalition *choose(vector<Coalition *> &offers);
};