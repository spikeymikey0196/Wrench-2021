#ifndef CREATURENODE_H
#define CREATURENODE_H

#include "Wrench.h"
#include "AIState.h"
#include "ActionState.h"
#include <memory>

using namespace std;
using namespace Wrench;

class CreatureNode : public PhysicsNode
{
	friend class AIState;
	friend class ActionState;

protected:
	unsigned int factionID;

	Range<int> Health;
	Range<int> Magic;

	shared_ptr<AIState> aiState;
	shared_ptr<ActionState> actionState;

public:
	CreatureNode(Scene *nScene, Model *nModel, const Vector3 &nPosition, const Vector3 &nOrientation, float nScale);
	virtual void Update(unsigned int Delta);
	virtual void Die();

	virtual void SetAIState(shared_ptr<AIState> nAIState);
	virtual void SetActionState(shared_ptr<ActionState> nActionState);
	
	shared_ptr<AIState> GetAIState();
	shared_ptr<ActionState> GetActionState();
};

#endif
