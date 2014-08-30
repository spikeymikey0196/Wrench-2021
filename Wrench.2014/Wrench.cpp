#include <Windows.h>
#include "Wrench.h"
#include "SDL_net.h"
#include "SOIL.h"
#include <stack>

using namespace std;

extern void Windows_SetWindowTitle(const char *text);

namespace Wrench
{
	stack<Scene *> sceneStack;

	void Init(int width, int height)
	{
		SDLNet_Init();
	};

	void Update(unsigned int Delta)
	{
		if (sceneStack.top())
			sceneStack.top()->Update(Delta);
	};

	void Render()
	{
		if (sceneStack.top())
			sceneStack.top()->Draw();
	};

	void PushScene(Scene *nScene)
	{
		sceneStack.push(nScene);
	};

	void PopScene()
	{
		//leak until converted to shared_ptr
		sceneStack.pop();
	};

	Scene *CurrentScene()
	{
		if (sceneStack.size() > 0)
			return sceneStack.top();
		return NULL;
	};

	unsigned int GetTicks()
	{
		return timeGetTime();
	};

	void SetWindowTitle(const char *text)
	{
		Windows_SetWindowTitle(text);
	};

	void TakeScreenshot(const char *filename)
	{
		SOIL_save_screenshot
			(
			filename,
			SOIL_SAVE_TYPE_BMP,
			0, 0, 800, 600		//temp
			);
	};
}
