#ifndef CALLBACKMANAGER_H
#define CALLBACKMANAGER_H

#include "RailCamera.h"
#include "WidgetNode.h"
#include <functional>
#include <map>
#include <string>

using namespace std;

namespace Wrench
{
	class UIElement;

	class CallbackManager
	{
	protected:
		map<string, function<void(UIElement*, int, int)>> uiCallback;
		map<string, function<void(RailCamera*)>> railCameraCallback;
		map<string, function<void(WidgetNode*, Node*, const Vector2 &mousePos)>> widgetCallback;

	public:
		CallbackManager();

		function<void(UIElement*, int, int)> AddUICallback(string name, function<void(UIElement*, int, int)> f);
		function<void(UIElement*, int, int)> GetUICallback(string name);

		function<void(RailCamera*)> AddRailCallback(string name, function<void(RailCamera*)> f);
		function<void(RailCamera*)> GetRailCallback(string name);

		function<void(WidgetNode*, Node*, const Vector2 &mousePos)> AddWidgetCallback(string name, function<void(WidgetNode*, Node*, const Vector2 &mousePos)> f);
		function<void(WidgetNode*, Node*, const Vector2 &mousePos)> GetWidgetCallback(string name);
	};
}

#endif
