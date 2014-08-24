#ifndef RAY_H
#define RAY_H

#include "Vector3.h"
#include "BoundingBox.h"

#include <list>
#include "tinyxml.h"

using namespace std;

namespace Wrench
{
	class Camera;
	class Viewport;

	class Ray
	{
	protected:
		Vector3 position;
		Vector3 direction;

	public:
		Ray();
		Ray(const Vector3 &nPosition, const Vector3 &nDirection);
		Ray(TiXmlElement *entry);
		bool Intersects(const BoundingBox &box, float &hitDistance);

		template<class T>
		T *ClosestIntersects(const list<T*> &n);

		static Ray FromScreenCoordinates(float x, float y, Camera &camera, Viewport &viewport);

		Vector3 Position();
		Vector3 Direction();
	};

	template<class T>
	T *Ray::ClosestIntersects(const list<T*> &n)
	{
		float hitDistance = 0.0f;
		float closestHit = FLT_MAX;
		T *closestNode = NULL;

		for (auto it : n)
		{
			if (Intersects(it->GetBounds(), hitDistance))
			{
				if (hitDistance < closestHit)
				{
					closestNode = it;
					closestHit = hitDistance;
				}
			}
		}

		return closestNode;
	};
}

#endif
