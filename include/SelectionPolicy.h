#pragma once

#include "Graph.h"
#include <vector>

using std::vector;

class Party;

class SelectionPolicy {
public:
    virtual int select(vector<Party *> &, int partyId, const Graph &graph) = 0;
    virtual ~SelectionPolicy() = default;
};

class MandatesSelectionPolicy : public SelectionPolicy {
public:
    int select(vector<Party *> &, int partyId, const Graph &graph) override;
};

class EdgeWeightSelectionPolicy : public SelectionPolicy {
public:
    int select(vector<Party *> &, int partyId, const Graph &graph) override;
};