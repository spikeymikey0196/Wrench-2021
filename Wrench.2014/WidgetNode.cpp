#include "WidgetNode.h"

namespace Wrench
{
	WidgetNode::WidgetNode(Scene *nScene, const Vector3 &nPosition, const Vector3 &nOrientation, float nScale, Model *nModel)
		: ModelNode(nScene, nPosition, nOrientation, nScale, nModel)
	{
		//
	};

	void WidgetNode::SetOnClick(function<void(WidgetNode*, Node*)> f)
	{
		onClickEvent = f;
	};

	void WidgetNode::SetOnHover(function<void(WidgetNode*, Node*)> f)
	{
		onHoverEvent = f;
	};

	void WidgetNode::OnClick(Node *caller)
	{
		if (onClickEvent)
			onClickEvent(this, caller);
	};

	void WidgetNode::OnHover(Node *caller)
	{
		if (onHoverEvent)
			onHoverEvent(this, caller);
	};

}
