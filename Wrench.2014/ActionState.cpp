#include "ActionState.h"

ActionState::ActionState(unsigned int nActionID, CreatureNode *nOwner)
{
	actionID = nActionID;
	owner = nOwner;
};

void ActionState::Update(unsigned int Delta)
{
	//
};

unsigned int ActionState::ActionID()
{
	return actionID;
}