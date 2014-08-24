#ifndef COLOR3_H
#define COLOR3_H

#include "tinyxml.h"

namespace Wrench
{
	class Color3
	{
	public:
		union
		{
			struct
			{
				float r;
				float g;
				float b;
			};

			float color[3];
		};

	public:
		Color3();
		Color3(float R, float G, float B);
		Color3(TiXmlElement *entry);

		Color3 operator + (const Color3 &param);
		Color3 operator - (const Color3 &param);
		Color3 operator * (const Color3 &param);
		Color3 operator / (const Color3 &param);

		void operator += (const Color3 &param);
		void operator -= (const Color3 &param);
		void operator *= (const Color3 &param);
		void operator /= (const Color3 &param);

		bool operator == (const Color3 &param);

		int RGBA();
		Color3 Lerp(const Color3 &v1, const Color3 &v2, double amount);
	};
}

#endif
