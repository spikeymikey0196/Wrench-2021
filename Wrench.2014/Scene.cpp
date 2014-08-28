#include "Scene.h"

namespace Wrench
{
	Scene::Scene()
	{
		content = new ContentManager();
		gravity = Vector3(0.0, 1.0, 0.0);
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

	};

	Vector3 Scene::Gravity()
	{
		return gravity;
	};

	Vector3 Scene::MillisecondGravity()
	{
		return gravity / 1000.0f;
	};

	void Scene::SetGravity(const Vector3 &nGravity)
	{
		gravity = nGravity;
	};
}
