#include "AIWatchNodeState.h"
#include "Wrench.h"
#include "CreatureNode.h"
#include "PlayerNode.h"
#include "Enums.h"
#include <cmath>

using namespace std;
using namespace Wrench;

AIWatchNodeState::AIWatchNodeState(CreatureNode *nOwner, PlayerNode *nTarget)
	: AIState(AI_WATCHNODE, nOwner)
{
	target = nTarget;
};

void AIWatchNodeState::Update(unsigned int Delta)
{
	if (owner && target)
	{
		Vector3 ownerPos = owner->GetTransform()->Position();
		Vector3 targetPos = target->GetTransform()->Position();

		float rad = atan2(ownerPos.x - targetPos.x, ownerPos.z - targetPos.z);

		Vector3 ownerOri = owner->GetTransform()->Orientation();
		ownerOri.y = rad;

		owner->GetTransform()->SetOrientation(ownerOri);
	}
};
