#include "WMath.h"

namespace Wrench
{
	double lerp(double value1, double value2, double amount)
	{
		return value1 + (value2 - value1) * amount;
	};

	double to_rad(double degree)
	{
		return degree * PI / 180.0;
	};

	double to_deg(double radian)
	{
		return radian * 180.0 / PI;
	};
}
