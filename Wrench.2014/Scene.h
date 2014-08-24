#ifndef SCENE_H
#define SCENE_H

#include "ContentManager.h"

namespace Wrench
{
	class Scene
	{
		friend class Node;
		friend class ModelNode;
		friend class Camera;

	protected:
		ContentManager *content;

	public:
		Scene();
		~Scene();
		virtual void Draw();
		virtual void Update(unsigned int Delta);
		virtual void KeyDown(int KeyID);
		virtual void KeyUp(int KeyID);
		virtual void MouseButtonDown(float x, float y);
		virtual void MouseButtonUp(float x, float y);
		virtual void MouseMotion(float x, float y);
	};
}

#endif