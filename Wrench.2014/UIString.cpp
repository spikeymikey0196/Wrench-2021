#include "UIString.h"

namespace Wrench
{
	UIString::UIString()
		: UIElement()
	{
		color = Color4(1, 1, 1, 1);
		scale = 1.0f;
		font = NULL;
		text = "";
	};

	UIString::UIString(UIElement *nParent, const Rect &nBounds, Font *nFont, string nText, const Color4 &nColor, float nScale)
		: UIElement()
	{
		color = nColor;
		scale = nScale;
		parent = nParent;
		bounds = nBounds;
		font = nFont;
		text = nText;
	};

	void UIString::Render()
	{
		if (font)
			font->Render(text, color, bounds, scale);
	};

	void UIString::SetText(string nText)
	{
		text = nText;
	};

}
