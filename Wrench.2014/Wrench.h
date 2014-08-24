#ifndef WRENCH_H
#define WRENCH_H

#include "BoundingBox.h"
#include "Brain.h"
#include "Camera.h"
#include "Color3.h"
#include "Color4.h"
#include "ContentManager.h"
#include "Light.h"
#include "Matrix.h"
#include "MissingModel.h"
#include "Model.h"
#include "ModelNode.h"
#include "ModelObj.h"
#include "Node.h"
#include "Packet.h"
#include "Quaternion.h"
#include "Range.h"
#include "Ray.h"
#include "Rect.h"
#include "RenderTarget.h"
#include "Scene.h"
#include "Shader.h"
#include "SkyBox.h"
#include "TCPSocket.h"
#include "TCPSocketSet.h"
#include "Texture.h"
#include "Transform.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Vertex.h"
#include "Viewport.h"
#include "WMath.h"

#include "tinyxml.h"

namespace Wrench
{
	void Init(int width, int height);
	void Update(unsigned int Delta);
	void Render();
	void PushScene(Scene *nScene);
	void PopScene();
	Scene *CurrentScene();
}

#endif