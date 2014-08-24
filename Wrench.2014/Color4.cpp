#include "Color4.h"
#include "WMath.h"
#include "Utils.h"
#include <cstring>

using namespace std;

namespace Wrench
{
Color4::Color4()
	{
		r = 1.0f;
		g = 1.0f;
		b = 1.0f;
		a = 1.0f;
	};

	Color4::Color4(float R, float G, float B, float A)
	{
		r = R;
		g = G;
		b = B;
		a = A;
	};

	Color4::Color4(const Color3 color, float A)
	{
		r = color.r;
		g = color.g;
		b = color.b;
		a = A;
	};

	Color4::Color4(TiXmlElement *entry)
	{
		XmlLoop(entry, it)
		{
			string valueStr = it->ValueStr();

			if (!valueStr.compare("R"))
				r = stof(it->GetText());
			else if (!valueStr.compare("G"))
				g = stof(it->GetText());
			else if (!valueStr.compare("B"))
				b = stof(it->GetText());
			else if (!valueStr.compare("A"))
				a = stof(it->GetText());
			else{}
		}
	};

	Color4 Color4::operator + (const Color4 &param)
	{
		Color4 temp;
		temp.r = r + param.r;
		temp.g = g + param.g;
		temp.b = b + param.b;
		temp.a = a + param.a;

		return temp;
	};

	Color4 Color4::operator - (const Color4 &param)
	{
		Color4 temp;
		temp.r = r - param.r;
		temp.g = g - param.g;
		temp.b = b - param.b;
		temp.a = a - param.a;

		return temp;
	};

	Color4 Color4::operator * (const Color4 &param)
	{
		Color4 temp;
		temp.r = r * param.r;
		temp.g = g * param.g;
		temp.b = b * param.b;
		temp.a = a * param.a;

		return temp;
	};

	Color4 Color4::operator / (const Color4 &param)
	{
		Color4 temp;
		temp.r = r / param.r;
		temp.g = g / param.g;
		temp.b = b / param.b;
		temp.a = a / param.a;

		return temp;
	};

	void Color4::operator += (const Color4 &param)
	{
		r += param.r;
		g += param.g;
		b += param.b;
		a += param.a;
	};

	void Color4::operator -= (const Color4 &param)
	{
		r -= param.r;
		g -= param.g;
		b -= param.b;
		a -= param.a;
	};

	void Color4::operator *= (const Color4 &param)
	{
		r *= param.r;
		g *= param.g;
		b *= param.b;
		a *= param.a;
	};

	void Color4::operator /= (const Color4 &param)
	{
		r /= param.r;
		g /= param.g;
		b /= param.b;
		a /= param.a;
	};

	bool Color4::operator == (const Color4 &param)
	{
		if(r == param.r && g == param.g && b == param.b && a == param.a)
			return true;

		return false;
	};

	int Color4::RGBA()
	{
		int value = 0;

		unsigned char buffer[4] = { 0 };
		buffer[0] = r * 255;
		buffer[1] = g * 255;
		buffer[2] = b * 255;
		buffer[3] = a * 255;

		memcpy(&value, &buffer[0], 4);

		return value;
	};

	Color4 Color4::Lerp(const Color4 &v1, const Color4 &v2, double amount)
	{
		return Color4(lerp(v1.r, v2.r, amount), lerp(v1.g, v2.g, amount), lerp(v1.b, v2.b, amount), lerp(v1.a, v2.a, amount));
	};
}
