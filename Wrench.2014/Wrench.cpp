#include "Wrench.h"
#include "SDL_net.h"
#include <stack>

using namespace std;

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
}
