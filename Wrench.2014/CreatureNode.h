#ifndef CREATURENODE_H
#define CREATURENODE_H

#include "Wrench.h"
#include "Stats.h"

using namespace Wrench;

class CreatureNode : public PhysicsNode
{
protected:
	unsigned int factionID;

	Stats stats;
	Range<int> Health;
	Range<int> Magic;

	unsigned int aiState;
	unsigned int actionState;

public:
	CreatureNode(Scene *nScene, Model *nModel, const Vector3 &nPosition, const Vector3 &nOrientation, float scale);

	virtual void Update(unsigned int Delta);
	virtual void TickAI(unsigned int Delta);

	virtual void Die();
};

#endif
