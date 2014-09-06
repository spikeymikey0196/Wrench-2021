#ifndef WAYPOINT_H
#define WAYPOINT_H

#include "Vector3.h"
#include <vector>

using namespace std;

namespace Wrench
{
	class Waypoint
	{
	protected:
		Vector3 position;
		vector<Waypoint *> adjacentWaypoints;
	public:
		Waypoint(const Vector3 &nPosition);
		void SetAdjacent(int index, Waypoint *wp);
		void AddAdjacent(Waypoint *wp);
		void ClearAdjacent();
		int AmountAdjacent();

		Waypoint *GetAdjacent(int index);

		Vector3 Position();
		void SetPosition(const Vector3 &nPosition);
	};
}

#endif
