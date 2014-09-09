#ifndef UISTRING_H
#define UISTRING_H

#include "Font.h"
#include "UIElement.h"
#include "Color4.h"

namespace Wrench
{
	class UIString : public UIElement
	{
	protected:
		Color4 color;
		float scale;
		Font *font;
		string text;

	public:
		UIString();
		UIString(UIElement *nParent, const Rect &nBounds, Font *nFont, string nText, const Color4 &nColor, float nScale);
		virtual void Render();
		virtual void SetText(string nText);
	};
}

#endif