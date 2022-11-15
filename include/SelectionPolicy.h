#pragma once
#include <vector>

using std::vector;

class Party;

class SelectionPolicy {
public:
    virtual Party& select(vector<Party*>&, int)=0;
};

class MandatesSelectionPolicy: public SelectionPolicy{
public:
    Party& select(vector<Party*>&, int);
};

class EdgeWeightSelectionPolicy: public SelectionPolicy{
public:
    Party& select(vector<Party*>&, int);
};