#include "Vector2.h"
#include "WMath.h"
#include "Utils.h"
#include <cmath>

using namespace std;

namespace Wrench
{
	Vector2::Vector2()
	{
		x = 0.0f;
		y = 0.0f;
	};

	Vector2::Vector2(float X, float Y)
	{
		x = X;
		y = Y;
	};

	Vector2::Vector2(TiXmlElement *entry)
	{
		XmlLoop(entry, it)
		{
			string valueStr = it->ValueStr();

			if (!valueStr.compare("X"))
				x = stof(it->GetText());
			else if (!valueStr.compare("Y"))
				y = stof(it->GetText());
			else{}
		}
	};

	Vector2 Vector2::operator * (float param)
	{
		return Vector2(x * param, y * param);
	};

	Vector2 Vector2::operator / (float param)
	{
		return Vector2(x / param, y / param);
	};

	Vector2 Vector2::operator + (const Vector2 &param)
	{
		return Vector2(x + param.x, y + param.y);
	};

	Vector2 Vector2::operator - (const Vector2 &param)
	{
		return Vector2(x - param.x, y - param.y);
	};

	Vector2 Vector2::operator * (const Vector2 &param)
	{
		return Vector2(x * param.x, y * param.y);
	};

	Vector2 Vector2::operator / (const Vector2 &param)
	{
		return Vector2(x / param.x, y / param.y);
	};

	void Vector2::operator += (const Vector2 &param)
	{
		x += param.x;
		y += param.y;
	};

	void Vector2::operator -= (const Vector2 &param)
	{
		x -= param.x;
		y -= param.y;
	};

	void Vector2::operator *= (const Vector2 &param)
	{
		x *= param.x;
		y *= param.y;
	};

	void Vector2::operator /= (const Vector2 &param)
	{
		x /= param.x;
		y /= param.y;
	};

	bool Vector2::operator == (const Vector2 &param)
	{
		if(x == param.x && y == param.y)
			return true;
		return false;
	};

	float Vector2::Distance(const Vector2 &param)
	{
		return sqrt(pow(param.x - x, 2) + pow(param.y-y,2));
	};

	float Vector2::Distance(const Vector2 &v1, const Vector2 &v2)
	{
		return sqrt(pow(v2.x - v1.x, 2) + pow(v2.y - v1.y,2));
	};

	Vector2 Vector2::Lerp(const Vector2 &v1, const Vector2 &v2, double amount)
	{
		return Vector2(lerp(v1.x, v2.x, amount), lerp(v1.y, v2.y, amount));
	};
}
