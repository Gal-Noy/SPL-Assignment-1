#pragma once
#include "Party.h"
#include "Graph.h"

class JoinPolicy {
    public:
        virtual Coalition& join(vector<Coalition&> offers)=0;
};

class MandatesJoinPolicy : public JoinPolicy {
    public:
        virtual Coalition& join(vector<Coalition&> offers);
};

class LastOfferJoinPolicy : public JoinPolicy {
    public:
        virtual Coalition& join(vector<Coalition&> offers);
};