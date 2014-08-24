#ifndef Rect_H
#define Rect_H

#include "Vector2.h"
#include "tinyxml.h"

namespace Wrench
{
	class Rect : public Vector2
	{
	public:
		float width;
		float height;

	public:
		Rect();
		Rect(const Vector2 &v, float Width, float Height);
		Rect(float X, float Y, float Width, float Height);
		Rect(TiXmlElement *entry);

		float Left();
		float Right();
		float Top();
		float Bottom();
		Vector2 Center();

		bool IsEmpty();

		bool Intersects(const Rect &other);
		bool Intersects(const Rect &other, Rect &resultArea);
		bool Intersects(const Vector2 &other);
	};
}

#endif
