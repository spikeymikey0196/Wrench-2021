#ifndef MOUSESTATE_H
#define MOUSESTATE_H

#include "Vector2.h"

namespace Wrench
{
	enum MouseButtons
	{
		BUTTON_LEFT		=	0,
		BUTTON_MIDDLE	=	1,
		BUTTON_RIGHT	=	2,
	};

	class MouseState
	{
	protected:
		Vector2 position;
		bool buttons[3];

	public:
		MouseState();

		bool IsButtonDown(int ButtonID);
		bool IsButtonUp(int ButtonID);
		Vector2 Position();

		static MouseState GetState();
	};
}

#endif
