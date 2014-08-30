#include "CallbackManager.h"

namespace Wrench
{
	CallbackManager::CallbackManager()
	{
		//
	};

	function<void(UIElement*, int, int)> CallbackManager::AddUICallback(string name, function<void(UIElement*, int, int)> f)
	{
		uiCallback[name] = f;
		return uiCallback[name];
	};

	function<void(UIElement*, int, int)> CallbackManager::GetUICallback(string name)
	{
		return uiCallback[name];
	};

	function<void(RailCamera*)> CallbackManager::AddRailCallback(string name, function<void(RailCamera*)> f)
	{
		railCameraCallback[name] = f;
		return railCameraCallback[name];
	};

	function<void(RailCamera*)> CallbackManager::GetRailCallback(string name)
	{
		return railCameraCallback[name];
	};

	function<void(WidgetNode*, Node*, const Vector2 &mousePos)> CallbackManager::AddWidgetCallback(string name, function<void(WidgetNode*, Node*, const Vector2 &mousePos)> f)
	{
		widgetCallback[name] = f;
		return widgetCallback[name];
	};

	function<void(WidgetNode*, Node*, const Vector2 &mousePos)> CallbackManager::GetWidgetCallback(string name)
	{
		return widgetCallback[name];
	};

}
