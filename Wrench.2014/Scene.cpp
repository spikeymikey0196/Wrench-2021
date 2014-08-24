#include "Scene.h"

namespace Wrench
{
	Scene::Scene()
	{
		content = new ContentManager();
	};

	Scene::~Scene()
	{
		if (content)
			delete content;
	}

	void Scene::Draw()
	{

	};

	void Scene::Update(unsigned int Delta)
	{

	};

	void Scene::KeyDown(int KeyID)
	{

	};

	void Scene::KeyUp(int KeyID)
	{

	};

	void Scene::MouseButtonDown(float x, float y)
	{

	};

	void Scene::MouseButtonUp(float x, float y)
	{

	};

	void Scene::MouseMotion(float x, float y)
	{

	}
}
