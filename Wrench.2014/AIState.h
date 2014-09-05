#ifndef AISTATE_H
#define AISTATE_H

class AIState
{
friend class CreatureNode;
friend class ActionState;

protected:
	CreatureNode *owner;
	unsigned int stateID;

public:
	AIState(unsigned int nStateID, CreatureNode *nOwner);
	virtual void Update(unsigned int Delta);
};

#endif