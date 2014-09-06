#include "ActionMoveToPoint.h"
#include "Transform.h"
#include "Enums.h"
#include "CreatureNode.h"

ActionMoveToPoint::ActionMoveToPoint(CreatureNode *nOwner, Waypoint *nTargetPoint, float nMoveSpeed)
	: ActionState(ACTION_MOVETOPOINT, nOwner)
{
	targetPoint = nTargetPoint;
	moveSpeed = nMoveSpeed;
};

void ActionMoveToPoint::Update(unsigned int Delta)
{
	if (owner)
	{
		Transform *t = owner->GetTransform();

		Vector3 ownerPos = t->Position();
		Vector3 targetPos = targetPoint->Position();

		if (Vector3::Distance(Vector3(ownerPos.x, 0, ownerPos.z), Vector3(targetPos.x, 0, targetPos.z)) < moveSpeed * 2.0f)	//ignore Y for gravity, temp fix
		{
			t->SetPosition(targetPos);
			owner->SetVelocity(Vector3(0, owner->Velocity().y, 0));
			owner->SetActionState(NULL);
			return;
		}


		float rad = atan2(ownerPos.x - targetPos.x, ownerPos.z - targetPos.z);

		Vector3 orientation = t->Orientation();
		orientation.y = rad;

		t->SetOrientation(orientation);

		Vector3 velocity = owner->Velocity();
		Vector3 nVelocity = t->GetMatrix().Forward() * moveSpeed;
		nVelocity.y = velocity.y;

		owner->SetVelocity(nVelocity);
	}
};
