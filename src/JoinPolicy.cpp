#include "JoinPolicy.h"
#include "Coalition.h"
#include "Simulation.h"

int MandatesJoinPolicy::choose(vector<int> &offers, Simulation &s) {
    Coalition &coalition = s.getCoalition(offers[0]);
    int index = 0;
    for (int i = 1; i < (int) offers.size(); i++) {
        Coalition &otherCoalition = s.getCoalition(offers[i]);
        if (otherCoalition.getMandates() > coalition.getMandates()) {
            index = i;
        }
    }
    return index;
}

int LastOfferJoinPolicy::choose(vector<int> &offers, Simulation &s) {
    return (int) offers.size() - 1;
}