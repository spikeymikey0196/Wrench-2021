#include "AIFollowPathState.h"
#include "Enums.h"
#include "CreatureNode.h"
#include "ActionMoveToPoint.h"

#include <vector>
#include <utility>

using namespace std;

AIFollowPathState::AIFollowPathState(CreatureNode *nOwner, const list<Waypoint*> &nPath, bool nLoop)
	: AIState(AI_FOLLOWPATH, nOwner)
{
	path = nPath;

	startingPoint = path.front();
	endingPoint = path.back();
	loop = nLoop;
};

void AIFollowPathState::Update(unsigned int Delta)
{
	if (owner)
	{
		shared_ptr<ActionState> oAction = owner->GetActionState();
		int oActionID = oAction ? oAction->ActionID() : 0;

		if (oActionID == ACTION_IDLE && path.size() > 0)
		{
			owner->SetActionState(make_shared<ActionMoveToPoint>(owner, path.front(), 0.1f));

			if (loop)
				path.push_back(path.front());
			path.pop_front();
		}
		else
		{
			if (path.size() == 0)
			{
				//pathing done
			}
		}
	}
};
