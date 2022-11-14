#pragma once
#include "Simulation.h"

class SelectionPolicy {
public:
    virtual Party select(const Graph, vector<Party>, int)=0;
};

class MandatesSelectionPolicy: public SelectionPolicy{
public:
    Party select(const Graph, vector<Party>, int);
};

class EdgeWeightSelectionPolicy: public SelectionPolicy{
public:
    Party select(const Graph, vector<Party>, int);
};