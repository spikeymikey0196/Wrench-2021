#ifndef UIELEMENT_H
#define UIELEMENT_H

#include "Transform.h"
#include "Rect.h"
#include "Texture.h"
#include "CallbackManager.h"
#include <functional>
#include <list>

using namespace std;

namespace Wrench
{
	class UIElement
	{
	protected:
		Rect bounds;
		Rect texCoords;
		Texture *texture;
		UIElement *parent;
		list<UIElement*> children;
		function<void(UIElement*, int, int)> onClick;

	public:
		UIElement();
		UIElement(UIElement *nParent, const Rect &nBounds, Texture *nTexture, const Rect &nTexCoords, function<void(UIElement*, int, int)> nOnClick);
		UIElement(UIElement *nParent, CallbackManager *callbackMgr, TiXmlElement *entry);

		virtual void Render();
		virtual UIElement *FindTargetElement(int x, int y);

		virtual void Click(int x, int y);
	};
}


#endif
