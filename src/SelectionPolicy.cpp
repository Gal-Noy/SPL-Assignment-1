#include "SelectionPolicy.h"

int MandatesSelectionPolicy::select(vector<Party *> &availableParties, int partyId, const Graph &graph) {
    int output = 0;
    for (int i = 1; (int) i < availableParties.size(); i++)
        if (availableParties[i]->getMandates() > availableParties[output]->getMandates())
            output = i;
    return output;
}


int EdgeWeightSelectionPolicy::select(vector<Party *> &availableParties, int partyId, const Graph &graph) {
    int output = 0;
    int maxEdgeWeight = -1;
    for (int i = 0; (int) i < availableParties.size(); i++){
        int currWeight = graph.getEdgeWeight(partyId, availableParties[i]->getId());
        if (currWeight > maxEdgeWeight) {
            output = i;
            maxEdgeWeight = currWeight;
        }
    }
    return output;
}