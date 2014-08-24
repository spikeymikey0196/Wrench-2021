#include "Brain.h"
#include <cstdlib>

namespace Wrench
{
	Brain::Brain()
	{
		owner = NULL;
	};

	Brain::Brain(Node *nOwner)
	{
		owner = nOwner;
	};

	IBrain::IBrain()
	{
		brain = NULL;
	};

	IBrain::IBrain(Brain *nBrain)
	{
		brain = nBrain;
	};

	void IBrain::Update(unsigned int Delta)
	{
		if (brain)
			brain->Update(Delta);
	};
}