#ifndef AIPATHINGSTATE_H
#define AIPATHINGSTATE_H

#include "AIState.h"
#include "Waypoint.h"

using namespace Wrench;

class AIPathingState : AIState
{
protected:
	Waypoint *startingPoint;
	Waypoint *endingPoint;

	//path here

public:
	AIPathingState(CreatureNode *nOwner, Waypoint *nStartingPoint, Waypoint *nEndingPoint);
	virtual void Update(unsigned int Delta);
};

#endif
