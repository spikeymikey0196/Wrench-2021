#ifndef CAMERA_H
#define CAMERA_H

#include "Vector3.h"
#include "Matrix.h"
#include "Viewport.h"
#include "tinyxml.h"

namespace Wrench
{
	class Camera
	{
	protected:
		Vector3 eye;
		Vector3 focus;
		Vector3 up;
		bool needsUpdate;
		Matrix worldMatrix;

	public:
		Camera();
		Camera(const Vector3 &nEye, const Vector3 &nFocus, const Vector3 &nUp);
		Camera(TiXmlElement *entry);

		static void Clear();
		virtual void Begin();
		virtual void Begin2D(const Viewport &viewport);
		static void End();

		void SetEye(const Vector3 &nEye);
		Vector3 Eye();

		void SetFocus(const Vector3 &nFocus);
		Vector3 Focus();

		void SetUp(const Vector3 &nUp);
		Vector3 Up();

		virtual Matrix GetMatrix();
	};
}

#endif
