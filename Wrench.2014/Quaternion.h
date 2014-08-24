#ifndef QUATERNION_H
#define QUATERNION_H

#include "tinyxml.h"

namespace Wrench
{
	class Quaternion
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
		Quaternion();
		Quaternion(float X, float Y, float Z, float W);
		Quaternion(TiXmlElement *entry);

		static Quaternion CreateFromYawPitchRoll(float pitch, float yaw, float roll);
	};
}

#endif
