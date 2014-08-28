#include "UI.h"

namespace Wrench
{
	UI::UI()
	{
		//
	};

	void UI::Render()
	{
		for (auto it : elements)
			it->Render();
	};

	UIElement *UI::AddElement(UIElement *e)
	{
		elements.push_back(e);
		return e;
	};

	void UI::RemoveElement(UIElement *e)
	{
		elements.remove(e);
	};

	bool UI::Click(int x, int y)
	{
		y = 600 - y;	//replace with height

		for (auto it : elements)
		{
			UIElement *temp = it->FindTargetElement(x, y);

			if (temp)
			{
				temp->Click(x, y);
				return true;
			}
		}

		return false;
	}
}
