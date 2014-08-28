#ifndef UIELEMENT_H
#define UIELEMENT_H

#include "Transform.h"
#include "Rect.h"
#include <functional>
#include <list>

using namespace std;

namespace Wrench
{
	class UIElement
	{
	protected:
		Rect bounds;
		UIElement *parent;
		list<UIElement*> children;
		function<void(UIElement*, int, int)> onClick;

	public:
		UIElement();
		UIElement(UIElement *nParent, const Rect &nBounds, function<void(UIElement*, int, int)> nOnClick);

		virtual void Render();
		virtual UIElement *FindTargetElement(int x, int y);

		virtual void Click(int x, int y);
	};
}


#endif
