#ifndef VECTOR3_H
#define VECTOR3_H

#include "Vector2.h"
#include "tinyxml.h"

namespace Wrench
{
	class Vector3
	{
	public:
		union
		{
			struct
			{
				float x;
				float y;
				float z;
			};

			float pos[3];
		};

	public:
		Vector3();
		Vector3(float X, float Y, float Z);
		Vector3(const Vector2 &vector, float Z);
		Vector3(TiXmlElement *entry);

		Vector3 operator + (float param);
		Vector3 operator - (float param);
		Vector3 operator * (float param);
		Vector3 operator / (float param);
		Vector3 operator + (const Vector3 &param);
		Vector3 operator - (const Vector3 &param);
		Vector3 operator * (const Vector3 &param);
		Vector3 operator / (const Vector3 &param);
		void operator += (const Vector3 &param);
		void operator -= (const Vector3 &param);
		void operator *= (const Vector3 &param);
		void operator /= (const Vector3 &param);
		bool operator == (const Vector3 &param);

		static Vector3 Cross(const Vector3 &v1, const Vector3 &v2);

		static Vector3 Normalize(const Vector3 &v1);

		static float Dot(const Vector3 &v, const Vector3 &w);

	    static float Length(const Vector3 &v);

	    static Vector3 Up();
	    static Vector3 Zero();

	    static Vector3 TriangleNormal(const Vector3 &vert1, const Vector3 &vert2, const Vector3 &vert3);

	    Vector3 Cross(const Vector3 &v2);

	    Vector3 Normalize();

	    float Dot(const Vector3 &w);

		float Length();

		float Distance(const Vector3 &param);
		static float Distance(const Vector3 &v1, const Vector3 &v2);
		static Vector3 Lerp(const Vector3 &v1, const Vector3 &v2, double amount);
	};
}

#endif
