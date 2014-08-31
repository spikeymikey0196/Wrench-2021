#ifndef CREATURENODE_H
#define CREATURENODE_H

#include "Wrench.h"
#include "Stats.h"

using namespace Wrench;

class CreatureNode : public UnitNode
{
protected:
	unsigned int factionID;

	Stats stats;
	Range<int> Health;
	Range<int> Magic;


public:
	CreatureNode(Scene *nScene);

	virtual void Update(unsigned int Delta);

	virtual void TickAI(unsigned int Delta);

	virtual void Die();
};

#endif
