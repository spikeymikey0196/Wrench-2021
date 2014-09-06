#include "UIElement.h"
#include "Utils.h"

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

	UIElement::UIElement(UIElement *nParent, const Rect &nBounds, Texture *nTexture, const Rect &nTexCoords, function<void(UIElement*, int, int)> nOnClick)
		: UIElement()
	{
		parent = nParent;
		bounds = nBounds;
		onClick = nOnClick;

		texture = nTexture;
		texCoords = nTexCoords;
	};

	UIElement::UIElement(UIElement *nParent, CallbackManager *callbackMgr, TiXmlElement *entry)
	{
		parent = nParent;
		string valueStr = "";

		XmlLoop(entry, uiEntry)
		{
			valueStr = uiEntry->ValueStr();

			if (!valueStr.compare("Bounds"))
				bounds = Rect(uiEntry);
			else if (!valueStr.compare("OnClick"))
			{
				onClick = callbackMgr->GetUICallback(uiEntry->GetText());
			}
			else{}
		}
	};

	void UIElement::Render()
	{
		if (texture) texture->Bind();

		glBegin(GL_QUADS);
			glTexCoord2f(texCoords.x, texCoords.y);
			glVertex2f(bounds.x, bounds.y);

			glTexCoord2f(texCoords.x, texCoords.y + texCoords.height);
			glVertex2f(bounds.x, bounds.y + bounds.height);

			glTexCoord2f(texCoords.x + texCoords.width, texCoords.y + texCoords.height);
			glVertex2f(bounds.x + bounds.width, bounds.y + bounds.height);

			glTexCoord2f(texCoords.x + texCoords.width, texCoords.y);
			glVertex2f(bounds.x+bounds.width, bounds.y);
		glEnd();

		if (texture) texture->Unbind();

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