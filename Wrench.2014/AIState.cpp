#include "AIState.h"

AIState::AIState(unsigned int nStateID, CreatureNode *nOwner)
{
	stateID = nStateID;
	owner = nOwner;
};

void AIState::Update(unsigned int Delta)
{
	//
};
