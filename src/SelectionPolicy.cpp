#include "SelectionPolicy.h"

MandatesSelectionPolicy* MandatesSelectionPolicy:: clone() const {
    return new MandatesSelectionPolicy(*this);
}

int MandatesSelectionPolicy::select(vector<Party *> &availableParties, int partyId, const Graph &graph) {
    unsigned int output = 0;
    for (unsigned int i = 1; i < availableParties.size(); i++)
        if (availableParties[i]->getMandates() > availableParties[output]->getMandates())
            output = (int) i;
    return (int) output;
}

EdgeWeightSelectionPolicy* EdgeWeightSelectionPolicy:: clone() const {
    return new EdgeWeightSelectionPolicy(*this);
}

int EdgeWeightSelectionPolicy::select(vector<Party *> &availableParties, int partyId, const Graph &graph){
    int output = 0;
    int maxEdgeWeight = -1;
    for (unsigned int i = 0; i < availableParties.size(); i++){
        int currWeight = graph.getEdgeWeight(partyId, availableParties[i]->getId());
        if (currWeight > maxEdgeWeight) {
            output = (int) i;
            maxEdgeWeight = currWeight;
        }
    }
    return (int) output;
}