#include "UIElement.h"

namespace Wrench
{
	UIElement::UIElement()
	{
		bounds = Rect(0, 0, 0, 0);
		parent = NULL;
	};

	UIElement::UIElement(UIElement *nParent, const Rect &nBounds)
		: UIElement()
	{
		parent = nParent;
		bounds = nBounds;
	};

	void UIElement::Render()
	{
		for (auto it : children)
			it->Render();
	};

	UIElement *UIElement::FindTargetElement(int x, int y)
	{
		//temp
		return this;
	};

}