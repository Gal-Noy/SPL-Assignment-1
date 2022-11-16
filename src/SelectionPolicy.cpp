#include "SelectionPolicy.h"

 Party &MandatesSelectionPolicy::select(vector<Party *> &availableParties, int partyId, const Graph &graph) {
    Party *output = availableParties[0];
    for (int i = 1; i < availableParties.size(); i++)
        if (availableParties[i]->getMandates() > output->getMandates())
            output = availableParties[i];
    return *output;
}


Party &EdgeWeightSelectionPolicy::select(vector<Party *> &availableParties, int partyId, const Graph &graph) {
    Party *output;
    int maxEdgeWeight = -1;
    for (auto & availableParty: availableParties) {
        int currWeight = graph.getEdgeWeight(partyId, availableParty->getId());
        if (currWeight > maxEdgeWeight) {
            output = availableParty;
            maxEdgeWeight = currWeight;
        }
    }
    return *output;
}