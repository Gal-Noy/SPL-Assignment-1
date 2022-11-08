#include "SelectionPolicy.h"
#include "Party.h"
#include "Graph.h"
#include <iostream>

Party EdgeWeightSelectionPolicy::select(const Graph &graph, vector<Party> parties, int partyId)
{
    Party output;
    int maxEdgeWeight = -1;
    for (int i = 0; i < parties.size(); i++){
        int currWeight = graph.getEdgeWeight(partyId, parties[i].getId());
        if (currWeight > maxEdgeWeight){
            output = parties[i];
            maxEdgeWeight = currWeight;
        }
    }
    return output;
}

Party MandatesSelectionPolicy::select(const Graph &graph, vector<Party> parties, int partyId)
{
    Party output = parties[0];
    for (int i = 1; i < parties.size(); i++)
        if (parties[i].getMandates() > output.getMandates())
            output = parties[i];
    return output;
}