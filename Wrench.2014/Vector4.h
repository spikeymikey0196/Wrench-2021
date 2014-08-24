#ifndef VECTOR4_H
#define VECTOR4_H

#include "Vector2.h"
#include "Vector3.h"
#include "tinyxml.h"

namespace Wrench
{
	class Vector4
	{
	public:
		union
		{
			struct
			{
				float x;
				float y;
				float z;
				float w;
			};

			float pos[4];
		};

	public:
		Vector4();
		Vector4(float X, float Y, float Z, float W);
		Vector4(const Vector2 &vector, float Z, float W);
		Vector4(const Vector3 &vector, float W);
		Vector4(TiXmlElement *entry);

		Vector4 operator + (float param);
		Vector4 operator - (float param);
		Vector4 operator * (float param);
		Vector4 operator / (float param);

		Vector4 operator + (const Vector4 &param);
		Vector4 operator - (const Vector4 &param);
		Vector4 operator * (const Vector4 &param);
		Vector4 operator / (const Vector4 &param);

		void operator += (const Vector4 &param);
		void operator -= (const Vector4 &param);
		void operator *= (const Vector4 &param);
		void operator /= (const Vector4 &param);
		bool operator == (const Vector4 &param);

		float Distance(const Vector4 &param);
		static float Distance(const Vector4 &v1, const Vector4 &v2);
		static Vector4 Lerp(const Vector4 &v1, const Vector4 &v2, double amount);
	};
}

#endif
