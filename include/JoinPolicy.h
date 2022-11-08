#pragma once
#include "Party.h"
#include "Graph.h"

class JoinPolicy {
    public:
        virtual Party select(const Graph &, vector<Party>, int)=0;
};

class MandatesJoinPolicy : public JoinPolicy {};

class LastOfferJoinPolicy : public JoinPolicy {};