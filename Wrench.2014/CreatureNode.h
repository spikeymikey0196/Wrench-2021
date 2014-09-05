#ifndef CREATURENODE_H
#define CREATURENODE_H

#include "Wrench.h"
#include "AIState.h"
#include "ActionState.h"

using namespace Wrench;

class CreatureNode : public PhysicsNode
{
	friend class AIState;
	friend class ActionState;

protected:
	unsigned int factionID;

	Range<int> Health;
	Range<int> Magic;

	AIState *aiState;
	ActionState *actionState;

public:
	CreatureNode(Scene *nScene, Model *nModel, const Vector3 &nPosition, const Vector3 &nOrientation, float nScale);
	virtual void Update(unsigned int Delta);
	virtual void Die();

	virtual void SetAIState(AIState *nAIState);
	virtual void SetActionState(ActionState *nActionState);
	
	AIState *GetAIState();
	ActionState *GetActionState();
};

#endif
