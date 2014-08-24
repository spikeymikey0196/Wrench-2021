#ifndef BRAIN_H
#define BRAIN_H

namespace Wrench
{
	class Node;

	class Brain
	{
	protected:
		Node *owner;

	public:
		Brain();
		Brain(Node *nOwner);
		virtual void Update(unsigned int Delta) = 0;
	};

	class IBrain
	{
	public:
		Brain *brain;
		IBrain();
		IBrain(Brain *nBrain);
		virtual void Update(unsigned int Delta);
	};
}

#endif