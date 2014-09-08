#ifndef PLANE_H
#define PLANE_H

#include "Vector3.h"

namespace Wrench
{
	class Plane
	{
	protected:
		Vector3 normal;
		float d;

	public:
		Plane(const Vector3 &nNormal, float D);
		Plane(const Vector3 &a, const Vector3 &b, const Vector3 &c);
		float ClassifyPoint(const Vector3 &point);
		float PerpendicularDistance(const Vector3 &point);
	};
}

#endif
