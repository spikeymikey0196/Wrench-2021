#include "KeyboardState.h"
#include <Windows.h>

namespace Wrench
{
	extern bool KeyState(int KeyID);

	KeyboardState::KeyboardState()
	{
		for (int a = 0; a < 256; a++)
			keys[a] = false;
	};

	bool KeyboardState::IsKeyDown(int KeyID)
	{
		return keys[KeyID];
	};

	bool KeyboardState::IsKeyUp(int KeyID)
	{
		return !keys[KeyID];
	};

	KeyboardState KeyboardState::GetState()
	{
		KeyboardState kbs;

		for (int a = 0; a < 256; a++)
			kbs.keys[a] = KeyState(a);

		return kbs;
	};

}
