#include "Vector3.h"
#include "WMath.h"
#include "Utils.h"
#include <cmath>
#include <string>

using namespace std;

namespace Wrench
{
	Vector3::Vector3()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	};

	Vector3::Vector3(float X, float Y, float Z)
	{
		x = X;
		y = Y;
		z = Z;
	};

	Vector3::Vector3(const Vector2 &vector, float Z)
	{
		x = vector.x;
		y = vector.y;
		z = Z;
	};

	Vector3::Vector3(TiXmlElement *entry)
	{
		XmlLoop(entry, it)
		{
			string valueStr = it->ValueStr();

			if (!valueStr.compare("X"))
				x = stof(it->GetText());
			else if(!valueStr.compare("Y"))
				y = stof(it->GetText());
			else if(!valueStr.compare("Z"))
				z = stof(it->GetText());
			else{}
		}
	};

	Vector3 Vector3::operator + (float param)
	{
		return Vector3(x + param, y + param, z + param);
	};

	Vector3 Vector3::operator - (float param)
	{
		return Vector3(x - param, y - param, z - param);
	};

	Vector3 Vector3::operator * (float param)
	{
		return Vector3(x * param, y * param, z * param);
	};

	Vector3 Vector3::operator / (float param)
	{
		return Vector3(x / param, y / param, z / param);
	};

	Vector3 Vector3::operator + (const Vector3 &param)
	{
		Vector3 temp;
		temp.x = x + param.x;
		temp.y = y + param.y;
		temp.z = z + param.z;
		return temp;
	};

	Vector3 Vector3::operator - (const Vector3 &param)
	{
		Vector3 temp;
		temp.x = x - param.x;
		temp.y = y - param.y;
		temp.z = z - param.z;
		return temp;
	};

	Vector3 Vector3::operator * (const Vector3 &param)
	{
		Vector3 temp;
		temp.x = x * param.x;
		temp.y = y * param.y;
		temp.z = z * param.z;
		return temp;
	};

	Vector3 Vector3::operator / (const Vector3 &param)
	{
		Vector3 temp;
		temp.x = x / param.x;
		temp.y = y / param.y;
		temp.z = z / param.z;
		return temp;
	};

	void Vector3::operator += (const Vector3 &param)
	{
		x += param.x;
		y += param.y;
		z += param.z;
	};

	void Vector3::operator -= (const Vector3 &param)
	{
		x -= param.x;
		y -= param.y;
		z -= param.z;
	};

	void Vector3::operator *= (const Vector3 &param)
	{
		x *= param.x;
		y *= param.y;
		z *= param.z;
	};

	void Vector3::operator /= (const Vector3 &param)
	{
		x /= param.x;
		y /= param.y;
		z /= param.z;
	};

	bool Vector3::operator == (const Vector3 &param)
	{
		if(x == param.x && y == param.y && z == param.z)
			return true;

		return false;
	};

	Vector3 Vector3::Cross(const Vector3 &v1, const Vector3 &v2)
	{
		Vector3 result;

		result.x = v1.y * v2.z - v1.z * v2.y;
		result.y = v1.z * v2.x - v1.x * v2.z;
		result.z = v1.x * v2.y - v1.y * v2.x;

		return result;
	};

	Vector3 Vector3::Normalize(const Vector3 &v1)
	{
		Vector3 result;
		float length = ((Vector3)v1).Length();

		result.x = v1.x / abs(length);
		result.y = v1.y / abs(length);
		result.z = v1.z / abs(length);

		return result;
	};

	float Vector3::Dot(const Vector3 &v, const Vector3 &w)
	{
		return (v.x*w.x + v.y*w.y + v.z*w.z);
	};

	float Vector3::Length(const Vector3 &v)
	{
		return sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
	};

	Vector3 Vector3::Up()
	{
		return Vector3(0,1,0);
	};

	Vector3 Vector3::Zero()
	{
		return Vector3(0,0,0);
	};

	Vector3 Vector3::TriangleNormal(const Vector3 &vert1, const Vector3 &vert2, const Vector3 &vert3)
	{
		Vector3 v1(vert2.x - vert1.x, vert2.y - vert1.y, vert2.z - vert1.z);
		Vector3 v2(vert3.x - vert1.x, vert3.y - vert1.y, vert3.z - vert1.z);

		Vector3 normal = Vector3::Cross(v1, v2);
		normal = Vector3::Normalize(normal);

		return normal;
	};

	Vector3 Vector3::Cross(const Vector3 &v2)
	{
		return Cross(*this, v2);
	};

	Vector3 Vector3::Normalize()
	{
		return Normalize(*this);
	};

	float Vector3::Dot(const Vector3 &w)
	{
		return Dot(*this, w);
	};

	float Vector3::Length()
	{
		return Length(*this);
	};

	float Vector3::Distance(const Vector3 &param)
	{
		return sqrt(pow(param.x - x, 2) + pow(param.y-y,2) + pow(param.z-z,2));
	};

	float Vector3::Distance(const Vector3 &v1, const Vector3 &v2)
	{
		return sqrt(pow(v2.x - v1.x, 2) + pow(v2.y - v1.y,2) + pow(v2.z - v1.z,2));
	};

	Vector3 Vector3::Lerp(const Vector3 &v1, const Vector3 &v2, double amount)
	{
		return Vector3(lerp(v1.x, v2.x, amount), lerp(v1.y, v2.y, amount), lerp(v1.z, v2.z, amount));
	};
}
