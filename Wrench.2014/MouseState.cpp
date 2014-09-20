#include "MouseState.h"
#include <Windows.h>

namespace Wrench
{
	extern Vector2 MousePos();
	extern bool KeyState(int KeyID);

	MouseState::MouseState()
	{
		position = Vector2(0, 0);
		buttons[0] = false;
		buttons[1] = false;
		buttons[2] = false;
	};

	bool MouseState::IsButtonDown(int ButtonID)
	{
		return buttons[ButtonID];
	};

	bool MouseState::IsButtonUp(int ButtonID)
	{
		return !buttons[ButtonID];
	};

	Vector2 MouseState::Position()
	{
		return position;
	};

	MouseState MouseState::GetState()
	{
		MouseState ms;

		ms.position = MousePos();
		ms.buttons[BUTTON_LEFT]		= KeyState(VK_LBUTTON);
		ms.buttons[BUTTON_MIDDLE]	= KeyState(VK_MBUTTON);
		ms.buttons[BUTTON_RIGHT]	= KeyState(VK_RBUTTON);

		return ms;
	};

}
