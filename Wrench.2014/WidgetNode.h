#ifndef WIDGETNODE_H
#define WIDGETNODE_H

#include "ModelNode.h"
#include <functional>

using namespace std;

namespace Wrench
{
	class WidgetNode : public ModelNode
	{
	protected:
		function<void(WidgetNode*, Node*)> onClickEvent;		//this, caller
		function<void(WidgetNode*, Node*)> onHoverEvent;	//this, caller

	public:
		WidgetNode(Scene *nScene, const Vector3 &nPosition, const Vector3 &nOrientation, float nScale, Model *nModel);

		virtual void SetOnClick(function<void(WidgetNode*, Node*)> f);
		virtual void SetOnHover(function<void(WidgetNode*, Node*)> f);

		virtual void OnClick(Node *caller);
		virtual void OnHover(Node *caller);
	};
}

#endif
