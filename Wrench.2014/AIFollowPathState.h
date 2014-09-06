#ifndef AIPATHINGSTATE_H
#define AIPATHINGSTATE_H

#include "AIState.h"
#include "Waypoint.h"
#include <list>

using namespace std;
using namespace Wrench;

class AIFollowPathState : public AIState
{
protected:
	Waypoint *startingPoint;
	Waypoint *endingPoint;

	list<Waypoint *> path;
	bool loop;

public:
	AIFollowPathState(CreatureNode *nOwner, const list<Waypoint*> &nPath, bool nLoop = false);
	virtual void Update(unsigned int Delta);
};

#endif
