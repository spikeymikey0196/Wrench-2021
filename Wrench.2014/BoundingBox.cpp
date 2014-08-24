#include "BoundingBox.h"
#include "Utils.h"

using namespace std;

namespace Wrench
{
	BoundingBox::BoundingBox()
	{
		min = Vector3::Zero();
		max = Vector3::Zero();
	};

	BoundingBox::BoundingBox(const Vector3 &nMin, const Vector3 &nMax)
	{
		min = nMin;
		max = nMax;
	};

	BoundingBox::BoundingBox(TiXmlElement *entry)
	{
		XmlLoop(entry, it)
		{
			string valueStr = it->ValueStr();

			if (!valueStr.compare("Min")) min = Vector3(it);
			if (!valueStr.compare("Max")) max = Vector3(it);
		}
	};

	bool BoundingBox::Intersects(const Vector3 &colPoint)
	{
		if (min.x > colPoint.x) return false;
		if (min.y > colPoint.y) return false;
		if (min.z > colPoint.z) return false;
		if (max.x < colPoint.x) return false;
		if (max.y < colPoint.y) return false;
		if (max.z < colPoint.z) return false;

		return true;
	};

	bool BoundingBox::Intersects(const BoundingBox &other)
	{
		if (min.x > other.max.x) return false;
		if (min.y > other.max.y) return false;
		if (min.z > other.max.z) return false;
		if (max.x < other.min.x) return false;
		if (max.y < other.min.y) return false;
		if (max.z < other.min.z) return false;

		return true;
	};

	void BoundingBox::SetMin(const Vector3 &nMin)
	{
		min = nMin;
	};

	Vector3 BoundingBox::Min()
	{
		return min;
	};

	void BoundingBox::SetMax(const Vector3 &nMax)
	{
		max = nMax;
	};

	Vector3 BoundingBox::Max()
	{
		return max;
	};

	BoundingBox BoundingBox::operator+ (const Vector3 &nOffset)
	{
		return BoundingBox(min + nOffset, max + nOffset);
	};

	BoundingBox BoundingBox::operator* (const Vector3 &nScale)
	{
		return BoundingBox(Vector3(min.x * nScale.x, min.y * nScale.y, min.z * nScale.z), Vector3(max.x * nScale.x, max.y * nScale.y, max.z * nScale.z));
	}
}
