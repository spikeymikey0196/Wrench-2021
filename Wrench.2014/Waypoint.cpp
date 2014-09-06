#include "Waypoint.h"

namespace Wrench
{
	Waypoint::Waypoint(const Vector3 &nPosition)
	{
		position = nPosition;
	};

	void Waypoint::SetAdjacent(int index, Waypoint *wp)
	{
		adjacentWaypoints[index] = wp;
	};

	void Waypoint::AddAdjacent(Waypoint *wp)
	{
		adjacentWaypoints.push_back(wp);
	};

	void Waypoint::ClearAdjacent()
	{
		adjacentWaypoints.clear();
	};

	int Waypoint::AmountAdjacent()
	{
		return adjacentWaypoints.size();
	};

	Waypoint *Waypoint::GetAdjacent(int index)
	{
		if (index >= 0 && index < adjacentWaypoints.size())
			return adjacentWaypoints[index];
		return NULL;
	};

	Vector3 Waypoint::Position()
	{
		return position;
	};

	void Waypoint::SetPosition(const Vector3 &nPosition)
	{
		position = nPosition;
	};

}
