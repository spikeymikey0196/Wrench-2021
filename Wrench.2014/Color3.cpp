#include "Color3.h"
#include "WMath.h"
#include "Utils.h"
#include <cstring>

using namespace std;

namespace Wrench
{
	Color3::Color3()
	{
		r = 1.0f;
		g = 1.0f;
		b = 1.0f;
	};

	Color3::Color3(float R, float G, float B)
	{
		r = R;
		g = G;
		b = B;
	};

	Color3::Color3(TiXmlElement *entry)
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
			else{}
		}
	};

	Color3 Color3::operator + (const Color3 &param)
	{
		Color3 temp;
		temp.r = r + param.r;
		temp.g = g + param.g;
		temp.b = b + param.b;

		return temp;
	};

	Color3 Color3::operator - (const Color3 &param)
	{
		Color3 temp;
		temp.r = r - param.r;
		temp.g = g - param.g;
		temp.b = b - param.b;

		return temp;
	};

	Color3 Color3::operator * (const Color3 &param)
	{
		Color3 temp;
		temp.r = r * param.r;
		temp.g = g * param.g;
		temp.b = b * param.b;

		return temp;
	};

	Color3 Color3::operator / (const Color3 &param)
	{
		Color3 temp;
		temp.r = r / param.r;
		temp.g = g / param.g;
		temp.b = b / param.b;

		return temp;
	};

	void Color3::operator += (const Color3 &param)
	{
		r += param.r;
		g += param.g;
		b += param.b;
	};

	void Color3::operator -= (const Color3 &param)
	{
		r -= param.r;
		g -= param.g;
		b -= param.b;
	};

	void Color3::operator *= (const Color3 &param)
	{
		r *= param.r;
		g *= param.g;
		b *= param.b;
	};

	void Color3::operator /= (const Color3 &param)
	{
		r /= param.r;
		g /= param.g;
		b /= param.b;
	};

	bool Color3::operator == (const Color3 &param)
	{
		if(r == param.r && g == param.g && b == param.b)
			return true;

		return false;
	};

	int Color3::RGBA()
	{
		int value = 0;

		unsigned char buffer[4] = { 0 };
		buffer[0] = r * 255;
		buffer[1] = g * 255;
		buffer[2] = b * 255;
		buffer[3] = 255;

		memcpy(&value, &buffer[0], 4);

		return value;
	}

	Color3 Color3::Lerp(const Color3 &v1, const Color3 &v2, double amount)
	{
		return Color3(lerp(v1.r, v2.r, amount), lerp(v1.g, v2.g, amount), lerp(v1.b, v2.b, amount));
	};
}
