#include "Waypoint.h"

namespace Wrench
{
	Waypoint::Waypoint(const Vector3 &nPosition)
	{
		position = nPosition;
		
		for (int a = 0; a < 4; a++)
			adjacentWaypoints[a] = NULL;
	};

	void Waypoint::SetAdjacent(int direction, Waypoint *wp)
	{
		adjacentWaypoints[direction] = wp;
	};

	Waypoint *Waypoint::GetAdjacent(int direction)
	{
		return adjacentWaypoints[direction];
	};

}
