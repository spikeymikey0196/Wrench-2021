#ifndef VECTOR2_H
#define VECTOR2_H

#include "tinyxml.h"

namespace Wrench
{
	class Vector2
	{
	public:
		union
		{
			struct
			{
				float x;
				float y;
			};

			float pos[2];
		};

	public:
		Vector2();
		Vector2(float X, float Y);
		Vector2(TiXmlElement *entry);

		Vector2 operator * (float param);
		Vector2 operator / (float param);
		Vector2 operator + (const Vector2 &param);
		Vector2 operator - (const Vector2 &param);
		Vector2 operator * (const Vector2 &param);
		Vector2 operator / (const Vector2 &param);
		void operator += (const Vector2 &param);
		void operator -= (const Vector2 &param);
		void operator *= (const Vector2 &param);
		void operator /= (const Vector2 &param);
		bool operator == (const Vector2 &param);

		float Distance(const Vector2 &param);
		static float Distance(const Vector2 &v1, const Vector2 &v2);
		static Vector2 Lerp(const Vector2 &v1, const Vector2 &v2, double amount);
	};
}

#endif
