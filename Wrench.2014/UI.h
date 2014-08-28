#ifndef UI_H
#define UI_H

#include "UIElement.h"
#include "Viewport.h"
#include <list>

using namespace std;

namespace Wrench
{
	class UI
	{
	protected:
		list<UIElement *> elements;

	public:
		UI();
		virtual void Render();

		virtual UIElement *AddElement(UIElement *e);
		virtual void RemoveElement(UIElement *e);

		virtual bool Click(int x, int y);
	};
}

#endif
