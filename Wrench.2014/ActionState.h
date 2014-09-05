#ifndef ACTIONSTATE_H
#define ACTIONSTATE_H

class ActionState
{
	friend class CreatureNode;
	friend class AIState;

protected:
	CreatureNode *owner;
	unsigned int actionID;

public:
	ActionState(unsigned int nActionID, CreatureNode *nOwner);
	virtual void Update(unsigned int Delta);
	unsigned int ActionID();
};


#endif
