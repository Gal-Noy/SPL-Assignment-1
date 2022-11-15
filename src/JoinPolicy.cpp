#include "JoinPolicy.h"

Coalition &MandatesJoinPolicy::join(vector<Coalition*>& offers)
{
    Coalition *maxMandates = offers[0];
    for (int i = 1; i < offers.size(); i++){
        if (offers[i] > maxMandates){
            maxMandates = offers[i];
        }
    }
    return *maxMandates;
}

Coalition &LastOfferJoinPolicy::join(vector<Coalition*>& offers)
{
    return *offers[offers.size()-1];
}