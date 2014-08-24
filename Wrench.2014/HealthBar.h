#ifndef HEALTHBAR_H
#define HEALTHBAR_H

#include "UIElement.h"
#include "Range.h"

using namespace Wrench;

class HealthBar : public UIElement
{
protected:
	Range<int> *target;

public:
	HealthBar(UIElement *nParent, const Rect &nBounds, Range<int> *nTarget);
	virtual void Render();
};

#endif