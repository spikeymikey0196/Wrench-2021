#ifndef WMATH_H
#define WMATH_H

namespace Wrench
{
	const double PI = 3.14159265359;

	double lerp(double value1, double value2, double amount);
	double to_rad(double degree);
	double to_deg(double radian);
}

#endif