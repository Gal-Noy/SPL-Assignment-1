#include "JoinPolicy.h"
#include "Coalition.h"
#include "Simulation.h"

MandatesJoinPolicy* MandatesJoinPolicy:: clone() const {
    return new MandatesJoinPolicy(*this);
}

int MandatesJoinPolicy::choose(vector<int> &offers, Simulation &s) {
    Coalition &coalition = s.getCoalition(offers[0]);
    int index = 0;
    for (unsigned int i = 1; i < offers.size(); i++) {
        Coalition &otherCoalition = s.getCoalition(offers[i]);
        if (otherCoalition.getMandates() > coalition.getMandates()) {
            index = i;
        }
    }
    return index;
}

LastOfferJoinPolicy* LastOfferJoinPolicy:: clone() const {
    return new LastOfferJoinPolicy(*this);
}

int LastOfferJoinPolicy::choose(vector<int> &offers, Simulation &s) {
    return offers.size() - 1;
}