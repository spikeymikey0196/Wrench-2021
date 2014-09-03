#include "Scene.h"
#include "PhysicsNode.h"
#include "Camera.h"
#include "Node.h"
#include "WorldChunkNode.h"
#include "PhysicsNode.h"

namespace Wrench
{
	Scene::Scene()
	{
		content = new ContentManager();
		callbacks = new CallbackManager();
		gravity = Vector3(0.0, 1.0, 0.0);
		skipFrame = false;
	};

	Scene::~Scene()
	{
		if (content)
			delete content;
	}

	void Scene::Draw()
	{
		Camera::Clear();

		for (auto rp : renderPasses)
		{
			glClear(GL_DEPTH_BUFFER_BIT);

			Matrix m = get<0>(rp)->GetMatrix();
			get<1>(rp)->UseViewport();
			get<0>(rp)->Begin();

//			skybox->Render(m);

			for (auto it : worldChunks)
				it->RenderTerrain(m);

			for (auto it : staticProps)
				it->Render(m);

			for (auto it : widgets)
				it->Render(m);

			for (auto it : units)
				it->Render(m);

			for (auto it : worldChunks)
				it->RenderWater(m);

			if (get<2>(rp))
			{
				get<0>(rp)->Begin2D(*get<1>(rp));
				get<2>(rp)->Render();
			}

			if (skipFrame)
			{
				skipFrame = false;
				return;
			}
		}

		Camera::End();
	};

	void Scene::Update(unsigned int Delta)
	{
		for (auto it : units)
		{
			((PhysicsNode*)it)->Update(Delta);
			((PhysicsNode*)it)->CollideProps(&staticProps);
			((PhysicsNode*)it)->CollideTerrain(&worldChunks);
		}
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

	void Scene::AddRenderPass(Camera *c, Viewport *v, UI *ui)
	{
		renderPasses.push_back(make_tuple(c, v, ui));
	};

	void Scene::ClearRenderPasses()
	{
		renderPasses.clear();
		skipFrame = true;
	};

	WorldChunkNode *Scene::AddWorldChunk(WorldChunkNode *chunk)
	{
		worldChunks.push_back(chunk);
		return chunk;
	};

	WidgetNode *Scene::AddWidget(WidgetNode *widget)
	{
		widgets.push_back((Node*)widget);
		return widget;
	};

	ModelNode *Scene::AddStaticProp(ModelNode *prop)
	{
		staticProps.push_back(prop);
		return prop;
	};

	PhysicsNode *Scene::AddUnit(PhysicsNode *unit)
	{
		units.push_back(unit);
		return unit;
	};

	void Scene::RemoveWorldChunk(WorldChunkNode *chunk)
	{
		worldChunks.remove(chunk);
	};

	void Scene::RemoveWidget(WidgetNode *widget)
	{
		widgets.remove((Node*)widget);
	};

	void Scene::RemoveStaticProp(ModelNode *prop)
	{
		staticProps.remove(prop);
	};

	void Scene::RemoveUnit(PhysicsNode *unit)
	{
		units.remove(unit);
	};

}
