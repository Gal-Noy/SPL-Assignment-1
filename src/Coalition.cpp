#include "Party.h"
#include "Agent.h"
#include <vector>

Coalition(vector<Agent> agent, vector<Party> existingParties, int mandates);

    int getMandates() const;
    void addMandates(int toAdd);
    vector<Party> getParties();
    void addParty(); //adds party to existing and removes from available
    vector<Party> getAvailableParties();