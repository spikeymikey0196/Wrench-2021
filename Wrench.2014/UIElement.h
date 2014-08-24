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

	public:
		UIElement();
		UIElement(UIElement *nParent, const Rect &nBounds);

		virtual void Render();
		virtual UIElement *FindTargetElement(int x, int y);

		//EVENTS
		function<int(int, int)> MouseDown;
		function<int(int, int)> MouseUp;
		function<int(int, int)> MouseMove;
	};
}


#endif
