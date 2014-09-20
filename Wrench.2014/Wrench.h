#ifndef WRENCH_H
#define WRENCH_H

#include "BasicShader.h"
#include "BasicMaterial.h"
#include "BoundingBox.h"
#include "BoundingSphere.h"
#include "Camera.h"
#include "Color3.h"
#include "Color4.h"
#include "CallbackManager.h"
#include "ContentManager.h"
#include "FollowCamera.h"
#include "Font.h"
#include "Light.h"
#include "Material.h"
#include "Matrix.h"
#include "MissingModel.h"
#include "Model.h"
#include "ModelNode.h"
#include "ModelObj.h"
#include "Node.h"
#include "Packet.h"
#include "Plane.h"
#include "Quaternion.h"
#include "RailCamera.h"
#include "Range.h"
#include "Ray.h"
#include "Rect.h"
#include "RenderTarget.h"
#include "Scene.h"
#include "Shader.h"
#include "SkyBox.h"
#include "TCPSocket.h"
#include "TCPSocketSet.h"
#include "Terrain.h"
#include "TerrainMaterial.h"
#include "Texture.h"
#include "Transform.h"
#include "UI.h"
#include "UIElement.h"
#include "UIString.h"
#include "Utils.h"
#include "PhysicsNode.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Vertex.h"
#include "VertexArray.h"
#include "Viewport.h"
#include "Water.h"
#include "WidgetNode.h"
#include "WMath.h"
#include "WorldChunkNode.h"

#include "tinyxml.h"

namespace Wrench
{
	void Init(int width, int height);
	void Update(unsigned int Delta);
	void Render();
	void PushScene(Scene *nScene);
	void PopScene();
	Scene *CurrentScene();
	unsigned int GetTicks();
	void SetWindowTitle(const char *text);
	void TakeScreenshot(const char *filename);

	int ScreenWidth();
	int ScreenHeight();

	Vector2 MousePos();
}

#endif
