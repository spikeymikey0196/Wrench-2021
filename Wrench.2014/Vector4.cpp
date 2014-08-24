#include "Vector4.h"
#include "WMath.h"
#include "Utils.h"
#include <cmath>

using namespace std;

namespace Wrench
{
	Vector4::Vector4()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
		w = 0.0f;
	};

	Vector4::Vector4(float X, float Y, float Z, float W)
	{
		x = X;
		y = Y;
		z = Z;
		w = W;
	};

	Vector4::Vector4(const Vector2 &vector, float Z, float W)
	{
		x = vector.x;
		y = vector.y;
		z = Z;
		w = W;
	};

	Vector4::Vector4(const Vector3 &vector, float W)
	{
		x = vector.x;
		y = vector.y;
		z = vector.z;
		w = W;
	};

	Vector4::Vector4(TiXmlElement *entry)
	{
		XmlLoop(entry, it)
		{
			string valueStr = it->ValueStr();

			if (!valueStr.compare("X"))
				x = stof(it->GetText());
			else if (!valueStr.compare("Y"))
				y = stof(it->GetText());
			else if (!valueStr.compare("Z"))
				z = stof(it->GetText());
			else if (!valueStr.compare("W"))
				w = stof(it->GetText());
			else{}
		}
	};

	Vector4 Vector4::operator + (float param)
	{
		return Vector4(x + param, y + param, z + param, w + param);
	};

	Vector4 Vector4::operator - (float param)
	{
		return Vector4(x - param, y - param, z - param, w - param);
	};

	Vector4 Vector4::operator * (float param)
	{
		return Vector4(x * param, y * param, z * param, w + param);
	};

	Vector4 Vector4::operator / (float param)
	{
		return Vector4(x / param, y / param, z / param, w / param);
	};

	Vector4 Vector4::operator + (const Vector4 &param)
	{
		Vector4 temp;
		temp.x = x + param.x;
		temp.y = y + param.y;
		temp.z = z + param.z;
		temp.w = w + param.w;

		return temp;
	};

	Vector4 Vector4::operator - (const Vector4 &param)
	{
		Vector4 temp;
		temp.x = x - param.x;
		temp.y = y - param.y;
		temp.z = z - param.z;
		temp.w = w - param.w;

		return temp;
	};

	Vector4 Vector4::operator * (const Vector4 &param)
	{
		Vector4 temp;
		temp.x = x * param.x;
		temp.y = y * param.y;
		temp.z = z * param.z;
		temp.w = w * param.w;

		return temp;
	};

	Vector4 Vector4::operator / (const Vector4 &param)
	{
		Vector4 temp;
		temp.x = x / param.x;
		temp.y = y / param.y;
		temp.z = z / param.z;
		temp.w = w / param.w;

		return temp;
	};

	void Vector4::operator += (const Vector4 &param)
	{
		x += param.x;
		y += param.y;
		z += param.z;
		w += param.w;
	};

	void Vector4::operator -= (const Vector4 &param)
	{
		x -= param.x;
		y -= param.y;
		z -= param.z;
		w -= param.w;
	};

	void Vector4::operator *= (const Vector4 &param)
	{
		x *= param.x;
		y *= param.y;
		z *= param.z;
		w *= param.w;
	};

	void Vector4::operator /= (const Vector4 &param)
	{
		x /= param.x;
		y /= param.y;
		z /= param.z;
		w /= param.w;
	};

	bool Vector4::operator == (const Vector4 &param)
	{
		if(x == param.x && y == param.y && z == param.z && w == param.w)
			return true;

		return false;
	};

	float Vector4::Distance(const Vector4 &param)
	{
		return sqrt(pow(param.x - x, 2) + pow(param.y-y,2) + pow(param.z-z,2) + pow(param.w-w,2));
	};

	float Vector4::Distance(const Vector4 &v1, const Vector4 &v2)
	{
		return sqrt(pow(v2.x - v1.x, 2) + pow(v2.y - v1.y,2) + pow(v2.z - v1.z,2) + pow(v2.w - v1.w,2));
	};

	Vector4 Vector4::Lerp(const Vector4 &v1, const Vector4 &v2, double amount)
	{
		return Vector4(lerp(v1.x, v2.x, amount), lerp(v1.y, v2.y, amount), lerp(v1.z, v2.z, amount), lerp(v1.w, v2.w, amount));
	};
}
