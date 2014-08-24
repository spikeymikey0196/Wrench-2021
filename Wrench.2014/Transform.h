#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Vector3.h"
#include "Matrix.h"
#include "tinyxml.h"

namespace Wrench
{
	class Transform
	{
	protected:
		Vector3 position;
		Vector3 orientation;
		Vector3 scale;

		Matrix matrix;
		bool needsRecalc;

		void Recalculate();

	public:
		Transform();
		Transform(const Vector3 &nPosition, const Vector3 &nOrientation, const Vector3 &nScale);
		Transform(const Vector3 &nPosition, const Vector3 &nOrientation, float nScale);
		Transform(TiXmlElement *entry);

		void SetPosition(const Vector3 &nPosition);
		Vector3 Position();

		void SetOrientation(const Vector3 &nOrientation);
		Vector3 Orientation();

		void SetScale(const Vector3 &nScale);
		void SetScale(float nScale);
		Vector3 Scale();

		Matrix GetMatrix();
	};
}

#endif
