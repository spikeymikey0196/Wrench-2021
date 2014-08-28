#include "UIElement.h"

#include "GLee.h"
#include <gl/GL.h>
#include <gl/GLU.h>

namespace Wrench
{
	UIElement::UIElement()
	{
		bounds = Rect(0, 0, 0, 0);
		parent = NULL;
	};

	UIElement::UIElement(UIElement *nParent, const Rect &nBounds, function<void(UIElement*, int, int)> nOnClick)
		: UIElement()
	{
		parent = nParent;
		bounds = nBounds;
		onClick = nOnClick;
	};

	void UIElement::Render()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
		glBegin(GL_QUADS);
			glVertex2f(bounds.x, bounds.y);
			glVertex2f(bounds.x, bounds.y + bounds.height);
			glVertex2f(bounds.x + bounds.width, bounds.y + bounds.height);
			glVertex2f(bounds.x+bounds.width, bounds.y);
		glEnd();


		for (auto it : children)
			it->Render();
	};

	UIElement *UIElement::FindTargetElement(int x, int y)
	{
		if (bounds.Intersects(Vector2(x, y)))
		{
			UIElement *e = this;

			for (auto it : children)
				if (it->bounds.Intersects(Vector2(x, y)))
					e = it;

			return e;
		}
		
		return NULL;
	};

	void UIElement::Click(int x, int y)
	{
		if (onClick)
			onClick(this,x,y);
	};

}