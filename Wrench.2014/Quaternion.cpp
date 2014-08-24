#include "Quaternion.h"
#include "Utils.h"
#include <cmath>
#include <string>

using namespace std;

namespace Wrench
{
	Quaternion::Quaternion()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
		w = 0.0f;
	};

	Quaternion::Quaternion(float X, float Y, float Z, float W)
	{
		x = X;
		y = Y;
		z = Z;
		w = W;
	};

	Quaternion::Quaternion(TiXmlElement *entry)
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

	Quaternion Quaternion::CreateFromYawPitchRoll(float pitch, float yaw, float roll)
	{
		Quaternion quaternion;
		float num9 = roll * 0.5f;
		float num6 = sin(num9);
		float num5 = cos(num9);
		float num8 = pitch * 0.5f;
		float num4 = sin(num8);
		float num3 = cos(num8);
		float num7 = yaw * 0.5f;
		float num2 = sin(num7);
		float num = cos(num7);
		quaternion.x = ((num * num4) * num5) + ((num2 * num3) * num6);
		quaternion.y = ((num2 * num3) * num5) - ((num * num4) * num6);
		quaternion.z = ((num * num3) * num6) - ((num2 * num4) * num5);
		quaternion.w = ((num * num3) * num5) + ((num2 * num4) * num6);
		return quaternion;
	};
}
