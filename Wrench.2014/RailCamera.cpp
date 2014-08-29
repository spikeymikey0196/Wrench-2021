#include "RailCamera.h"
#include "Wrench.h"

namespace Wrench
{
	RailCamera::RailCamera(const Vector3 &nEye, const Vector3 &nFocus)
		: Camera(nEye, nFocus, Vector3(0,1,0))
	{
		running = false;
		railProgress = 0.0f;
		lastFrameTime = Wrench::GetTicks();
		rail = vector<tuple<Vector3, Vector3>>();

		AddRailPoint(nEye, nFocus);
	};

	void RailCamera::AddRailPoint(const Vector3 &eyePos, const Vector3 &focus)
	{
		rail.push_back(make_tuple(eyePos, focus));
	};

	void RailCamera::Play()
	{
		running = true;
		railProgress = 0.0f;
		lastFrameTime = Wrench::GetTicks();
	};

	void RailCamera::Stop()
	{
		running = false;
	};

	void RailCamera::Begin()
	{
		unsigned int currentTime = Wrench::GetTicks();
		unsigned int delta = currentTime - lastFrameTime;
		railProgress += 0.00001f * (float)delta;

		tuple<Vector3, Vector3> p1 = GetRailPoint(railProgress);
		tuple<Vector3, Vector3> p2 = GetRailPoint(railProgress+1);

		float diff = railProgress - (float)((int)railProgress);

		SetEye(Vector3::Lerp(get<0>(p1), get<0>(p2), diff));
		SetFocus(Vector3::Lerp(get<1>(p1), get<1>(p2), diff));

		Camera::Begin();
	};
	
	tuple<Vector3, Vector3> RailCamera::GetRailPoint(int ID)
	{
		if (ID >= rail.size())
			return rail[rail.size() - 1];
		return rail[ID];
	};
}
