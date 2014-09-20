#ifndef KEYBOARDSTATE_H
#define KEYBOARDSTATE_H

namespace Wrench
{
	class KeyboardState
	{
	protected:
		bool keys[256];

	public:
		KeyboardState();
		bool IsKeyDown(int KeyID);
		bool IsKeyUp(int KeyID);
		static KeyboardState GetState();
	};
}

#endif