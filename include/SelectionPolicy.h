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
    MandatesSelectionPolicy* clone() const override;
    int select(vector<Party *> &, int partyId, const Graph &graph) override;
    ~MandatesSelectionPolicy() override = default;
};

class EdgeWeightSelectionPolicy : public SelectionPolicy {
public:
    EdgeWeightSelectionPolicy* clone() const override;
    int select(vector<Party *> &, int partyId, const Graph &graph) override;
    ~EdgeWeightSelectionPolicy() override = default;
};