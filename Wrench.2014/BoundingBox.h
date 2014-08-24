#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include "Vector3.h"
#include "tinyxml.h"

namespace Wrench
{
	class BoundingBox
	{
	protected:
		Vector3 min;
		Vector3 max;

	public:
		BoundingBox();
		BoundingBox(const Vector3 &nMin, const Vector3 &nMax);
		BoundingBox(TiXmlElement *entry);

		bool Intersects(const Vector3 &colPoint);
		bool Intersects(const BoundingBox &other);

		void SetMin(const Vector3 &nMin);
		Vector3 Min();

		void SetMax(const Vector3 &nMax);
		Vector3 Max();

		BoundingBox operator+ (const Vector3 &nOffset);
		BoundingBox operator* (const Vector3 &nScale);
	};
}

#endif
