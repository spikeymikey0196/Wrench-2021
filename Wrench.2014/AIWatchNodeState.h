#ifndef AIWATCHNODE_H
#define AIWATCHNODE_H

#include "AIState.h"

class PlayerNode;

class AIWatchNodeState : public AIState
{
protected:
	PlayerNode *target;

public:
	AIWatchNodeState(CreatureNode *nOwner, PlayerNode *nTarget);
	virtual void Update(unsigned int Delta);
};


#endif
