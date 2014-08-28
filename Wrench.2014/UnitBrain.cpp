#include "UnitBrain.h"
#include <stdlib.h>

namespace Wrench
{
	UnitBrain::UnitBrain()
	{
		owner = NULL;
	};

	UnitBrain::UnitBrain(UnitNode *nOwner)
	{
		owner = nOwner;
	};

	void UnitBrain::Update(unsigned int Delta)
	{

	};

}
