#ifndef BOUNDINGSPHERE_H
#define BOUNDINGSHPERE_H

#include "Vector3.h"

namespace Wrench
{
	class BoundingSphere
	{
	protected:
		Vector3 position;
		float radius;

	public:
		BoundingSphere(const Vector3 &nPosition, float nRadius);
		bool Intersects(const BoundingSphere &other);
		bool Intersects(const Vector3 &other);
	};
}

#endif
