#include "JoinPolicy.h"
#include "Coalition.h"

int MandatesJoinPolicy::choose(vector<Coalition *> &offers) {
    int maxMandates = 0;
    for (unsigned int i = 1; i < offers.size(); i++) {
        if (offers[i]->getMandates() > offers[maxMandates]->getMandates()) {
            maxMandates = i;
        }
    }
    return maxMandates;
}

int LastOfferJoinPolicy::choose(vector<Coalition *> &offers) {
    return (int) offers.size() - 1;
}