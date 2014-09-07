#ifndef AIWANDERSTATE_H
#define AIWANDERSTATE_H

#include "AIFollowPathState.h"
#include "Terrain.h"

using namespace Wrench;

class AIWanderState : public AIFollowPathState
{
protected:
	Terrain *terrain;
	Vector3 centerPoint;
	float wanderDistance;

public:
	AIWanderState(CreatureNode *nOwner, Terrain *nTerrain, const Vector3 &nCenterPoint, float nWanderDistance);
	virtual void Update(unsigned int Delta);
};

#endif
