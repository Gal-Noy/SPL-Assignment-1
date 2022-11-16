#pragma once

#include "Graph.h"
#include <vector>

using std::vector;

class Party;

class SelectionPolicy {
public:
    virtual Party *select(vector<Party *> &, int partyId, Graph &graph) = 0;
};

class MandatesSelectionPolicy : public SelectionPolicy {
public:
    Party *select(vector<Party *> &, int partyId, Graph &graph);
};

class EdgeWeightSelectionPolicy : public SelectionPolicy {
public:
    Party *select(vector<Party *> &, int partyId, Graph &graph);
};