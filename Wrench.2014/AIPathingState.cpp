#include "AIPathingState.h"
#include "Enums.h"
#include "CreatureNode.h"

AIPathingState::AIPathingState(CreatureNode *nOwner, Waypoint *nStartingPoint, Waypoint *nEndingPoint)
	: AIState(AI_PATHING, nOwner)
{
	startingPoint = nStartingPoint;
	endingPoint = nEndingPoint;
};

void AIPathingState::Update(unsigned int Delta)
{
	if (owner)
	{
		ActionState *oAction = owner->GetActionState();
		int oActionID = oAction ? oAction->ActionID() : 0;

		if (oActionID == ACTION_IDLE)
		{
			//set action to move to point
		}
	}
};
