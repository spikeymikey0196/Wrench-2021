#ifndef WAYPOINT_H
#define WAYPOINT_H

#include "Vector3.h"

namespace Wrench
{
	enum WaypointDirections
	{
		WAYPOINT_XPLUS = 0,
		WAYPOINT_YPLUS = 1,
		WAYPOINT_XMINUS = 2,
		WAYPOINT_YMINUS = 3,
	};

	class Waypoint
	{
	protected:
		Vector3 position;
		Waypoint *adjacentWaypoints[4];
	public:
		Waypoint(const Vector3 &nPosition);
		void SetAdjacent(int direction, Waypoint *wp);
		Waypoint *GetAdjacent(int direction);
	};
}

#endif
