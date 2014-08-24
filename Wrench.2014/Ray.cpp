#include "Ray.h"
#include "Camera.h"
#include "Viewport.h"
#include "Utils.h"
#include <cmath>
#include <cfloat>

using namespace std;

namespace Wrench
{
	Ray::Ray()
	{
		position = Vector3::Zero();
		direction = Vector3::Zero();
	};

	Ray::Ray(const Vector3 &nPosition, const Vector3 &nDirection)
	{
		position = nPosition;
		direction = nDirection;
	};

	Ray::Ray(TiXmlElement *entry)
	{
		XmlLoop(entry, it)
		{
			string valueStr = it->ValueStr();

			if (!valueStr.compare("Position")) position = Vector3(it);
			if (!valueStr.compare("Direction")) direction = Vector3(it);
		}
	}

	bool Ray::Intersects(const BoundingBox &box, float &hitDistance)
	{
		BoundingBox &Box = ((BoundingBox)box);
		const float Epsilon = 1e-6f;

		float tMin = FLT_MIN;
		float tMax = FLT_MIN;

		hitDistance = 0.0f;

		//X
		if (abs(direction.x) < Epsilon)
		{
			if (position.x < Box.Min().x || position.x > Box.Max().x)
				return false;
		}
		else
		{
			tMin = (Box.Min().x - position.x) / direction.x;
			tMax = (Box.Max().x - position.x) / direction.x;

			if (tMin > tMax)
			{
				float temp = tMin;
				tMin = tMax;
				tMax = temp;
			}
		}
		
		//Y
		if (abs(direction.y) < Epsilon)
		{
			if (position.y < Box.Min().y || position.y > Box.Max().y)
				return false;
		}
		else
		{
			float tMinY = (Box.Min().y - position.y) / direction.y;
			float tMaxY = (Box.Max().y - position.y) / direction.y;

			if (tMinY > tMaxY)
			{
				float temp = tMinY;
				tMinY = tMaxY;
				tMaxY = temp;
			}

			if ((tMin != FLT_MIN && tMin > tMaxY) || (tMax != FLT_MIN && tMinY > tMax))
				return false;

			if (tMin == FLT_MIN || tMinY > tMin) tMin = tMinY;
			if (tMax == FLT_MIN || tMaxY < tMax) tMax = tMaxY;
		}

		//Z
		if (abs(direction.z) < Epsilon)
		{
			if (position.z < Box.Min().z || position.z > Box.Max().z)
				return false;
		}
		else
		{
			float tMinZ = (Box.Min().z - position.z) / direction.z;
			float tMaxZ = (Box.Max().z - position.z) / direction.z;

			if (tMinZ > tMaxZ)
			{
				float temp = tMinZ;
				tMinZ = tMaxZ;
				tMaxZ = temp;
			}

			if ((tMin != FLT_MIN && tMin > tMaxZ) || (tMax != FLT_MIN && tMinZ > tMax))
				return false;

			if (tMin == FLT_MIN || tMinZ > tMin) tMin = tMinZ;
			if (tMax == FLT_MIN || tMaxZ < tMax) tMax = tMaxZ;
		}

		if ((tMin != FLT_MIN && tMin < 0) && tMax > 0)
		{
			hitDistance = 0.0f;
			return true;
		}

		if (tMin < 0) return false;

		hitDistance = tMin;
		return true;
	};

	Vector3 Ray::Position()
	{
		return position;
	};

	Vector3 Ray::Direction()
	{
		return direction;
	};

	Ray Ray::FromScreenCoordinates(float x, float y, Camera &camera, Viewport &viewport)
	{
		float width = viewport.Bounds().width;
		float height = viewport.Bounds().height;

		Vector3 view = camera.Focus() - camera.Eye();
		view = Vector3::Normalize(view);

		Vector3 h = Vector3::Cross(view, camera.Up());
		h = Vector3::Normalize(h);

		Vector3 v = Vector3::Cross(h, view);
		v = Vector3::Normalize(v);

		float fovy = 45.0f; //field of view
		float rad = fovy * 3.14 / 180.0f;

		float vLength = tan(rad / 2) * viewport.Near();
		float hLength = vLength * width / height;

		v = v * vLength;
		h = h * hLength;

		x -= width / 2.0f;
		y -= height / 2.0f;

		y /= (height / 2.0f);
		x /= (width / 2.0f);

		Vector3 pos = camera.Eye() + view * viewport.Near() + h*x + v*y;
		Vector3 dir = pos - camera.Eye();

		Ray r = Ray(pos, dir);
		return r;
	}
};
