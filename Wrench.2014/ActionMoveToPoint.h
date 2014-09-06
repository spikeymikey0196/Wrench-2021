#ifndef ACTIONMOVETOPOINT_H
#define ACTIONMOVETOPOINT_H

#include "ActionState.h"
#include "Waypoint.h"

using namespace Wrench;

class ActionMoveToPoint : public ActionState
{
protected:
	Waypoint *targetPoint;
	float moveSpeed;

public:
	ActionMoveToPoint(CreatureNode *nOwner, Waypoint *nTargetPoint, float nMoveSpeed);
	virtual void Update(unsigned int Delta);
};

#endif
