#ifndef COLOR4_H
#define COLOR4_H

#include "Color3.h"
#include "tinyxml.h"

namespace Wrench
{
	class Color4
	{
	public:
		union
		{
			struct
			{
				float r;
				float g;
				float b;
				float a;
			};

			float color[4];
		};

	public:
		Color4();
		Color4(float R, float G, float B, float A);
		Color4(const Color3 color, float A);
		Color4(TiXmlElement *entry);

		Color4 operator + (const Color4 &param);
		Color4 operator - (const Color4 &param);
		Color4 operator * (const Color4 &param);
		Color4 operator / (const Color4 &param);

		void operator += (const Color4 &param);
		void operator -= (const Color4 &param);
		void operator *= (const Color4 &param);
		void operator /= (const Color4 &param);

		bool operator == (const Color4 &param);

		int RGBA();
		Color4 Lerp(const Color4 &v1, const Color4 &v2, double amount);
	};
}

#endif
