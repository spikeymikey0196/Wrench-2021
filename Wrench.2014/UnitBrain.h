#ifndef UNITBRAIN_H
#define UNITBRAIN_H

namespace Wrench
{
	class UnitNode;

	class UnitBrain
	{
	protected:
		UnitNode *owner;

	public:
		UnitBrain();
		UnitBrain(UnitNode *nOwner);

		virtual void Update(unsigned int Delta);
	};
}

#endif
