#include "Plane.h"
#include <cmath>

using namespace std;

namespace Wrench
{
	Plane::Plane(const Vector3 &nNormal, float D)
	{
		normal = nNormal;
		d = D;
	};

	Plane::Plane(const Vector3 &a, const Vector3 &b, const Vector3 &c)
	{
		Vector3 ab = ((Vector3)b) - a;
		Vector3 ac = ((Vector3)c) - a;

		Vector3 cross = Vector3::Cross(ab, ac);
		normal = Vector3::Normalize(cross);

		d = -(Vector3::Dot(normal, a));
	};

	float Plane::ClassifyPoint(const Vector3 &point)
	{
		return point.x * normal.x + point.y * normal.y + point.z * normal.z + d;
	};

	float Plane::PerpendicularDistance(const Vector3 &point)
	{
		return abs((normal.x * point.x + normal.y * point.y + normal.z * point.z)
			/ sqrt(normal.x * normal.x + normal.y * normal.y + normal.z * normal.z));
	};

}
