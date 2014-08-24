#include "Camera.h"
#include "GLee.h"
#include "Utils.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include <string>

extern void WinSwapBuffer();

using namespace std;

namespace Wrench
{
	Camera::Camera()
	{
		eye = Vector3::Zero();
		focus = Vector3::Zero();
		up = Vector3(0, 1, 0);

		worldMatrix = Matrix::Identity();
		needsUpdate = true;
	};

	Camera::Camera(const Vector3 &nEye, const Vector3 &nFocus, const Vector3 &nUp)
	{
		eye = nEye;
		focus = nFocus;
		up = nUp;

		worldMatrix = Matrix::Identity();
		needsUpdate = true;
	};

	Camera::Camera(TiXmlElement *entry)
		: Camera()
	{
		XmlLoop(entry, it)
		{
			string valueStr = it->ValueStr();

			if (!valueStr.compare("Eye")) eye = Vector3(it);
			if (!valueStr.compare("Focus")) focus = Vector3(it);
			if (!valueStr.compare("Up")) up = Vector3(it);
		}
	};

	void Camera::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	};

	void Camera::Begin()
	{
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glEnable(GL_LIGHTING);
		glEnable(GL_DITHER);
		gluLookAt(eye.x, eye.y, eye.z, focus.x, focus.y, focus.z, up.x, up.y, up.z);
	};

	void Camera::Begin2D(const Viewport &viewport)
	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		glOrtho(0, ((Viewport)viewport).Bounds().width, ((Viewport)viewport).Bounds().height, 0, -1, 1);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glDisable(GL_DEPTH_TEST);
		glDisable(GL_LIGHTING);
		glDisable(GL_DITHER);
	};

	void Camera::End()
	{
		WinSwapBuffer();
	};

	void Camera::SetEye(const Vector3 &nEye)
	{
		eye = nEye;
		needsUpdate = true;
	};

	Vector3 Camera::Eye()
	{
		return eye;
	};

	void Camera::SetFocus(const Vector3 &nFocus)
	{
		focus = nFocus;
		needsUpdate = true;
	};

	Vector3 Camera::Focus()
	{
		return focus;
	};

	void Camera::SetUp(const Vector3 &nUp)
	{
		up = nUp;
		needsUpdate = true;
	};

	Vector3 Camera::Up()
	{
		return up;
	};

	Matrix Camera::GetMatrix()
	{
		if (needsUpdate)
		{
			worldMatrix = Matrix::CreateLookAt(eye, focus, up);
			needsUpdate = false;
		}

		return worldMatrix;
	};
}