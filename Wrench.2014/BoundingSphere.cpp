#include "BoundingSphere.h"

namespace Wrench
{
	BoundingSphere::BoundingSphere(const Vector3 &nPosition, float nRadius)
	{
		position = nPosition;
		radius = nRadius;
	};

	bool BoundingSphere::Intersects(const BoundingSphere &other)
	{
		if (Vector3::Distance(position, other.position) <= radius + other.radius)
			return true;
		return false;
	};

	bool BoundingSphere::Intersects(const Vector3 &other)
	{
		if (Vector3::Distance(position, other) <= radius)
			return true;
		return false;
	};

}
