#include "WidgetNode.h"

namespace Wrench
{
	WidgetNode::WidgetNode(Scene *nScene, const Vector3 &nPosition, const Vector3 &nOrientation, float nScale, Model *nModel)
		: ModelNode(nScene, nPosition, nOrientation, nScale, nModel)
	{
		//
	};

	void WidgetNode::SetOnClick(function<void(WidgetNode*, Node*, const Vector2 &mousePos)> f)
	{
		onClickEvent = f;
	};

	void WidgetNode::SetOnHover(function<void(WidgetNode*, Node*, const Vector2 &mousePos)> f)
	{
		onHoverEvent = f;
	};

	void WidgetNode::OnClick(Node *caller, const Vector2 &mousePos)
	{
		if (onClickEvent)
			onClickEvent(this, caller, mousePos);
	};

	void WidgetNode::OnHover(Node *caller, const Vector2 &mousePos)
	{
		if (onHoverEvent)
			onHoverEvent(this, caller, mousePos);
	};

}
