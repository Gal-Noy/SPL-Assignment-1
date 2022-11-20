#pragma once

#include "Graph.h"
#include <vector>

using std::vector;

class Party;

class SelectionPolicy {
public:
    virtual SelectionPolicy* clone() const = 0;
    virtual int select(vector<Party *> &, int partyId, const Graph &graph) = 0;
    virtual ~SelectionPolicy() = default;
};

class MandatesSelectionPolicy : public SelectionPolicy {
public:
    virtual MandatesSelectionPolicy* clone() const override;
    int select(vector<Party *> &, int partyId, const Graph &graph) override;
};

class EdgeWeightSelectionPolicy : public SelectionPolicy {
public:
    virtual EdgeWeightSelectionPolicy* clone() const override;
    int select(vector<Party *> &, int partyId, const Graph &graph) override;
};