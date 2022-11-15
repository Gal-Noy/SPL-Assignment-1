#pragma once
#include <vector>
#include "Party.h"

using std::vector;

class Graph
{
public:
    Graph(vector<Party> vertices, vector<vector<int>> edges);
    // TODO: Rule of Five (I believe not, it's just a graph without any copies and shit)
    int getMandates(int partyId) const;
    int getEdgeWeight(int v1, int v2) const;
    int getNumVertices() const;
    const Party &getParty(int partyId) const;

private:
    vector<Party> mVertices;
    vector<vector<int>> mEdges;
};
