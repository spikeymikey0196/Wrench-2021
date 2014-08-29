#ifndef RAILCAMERA_H
#define RAILCAMERA_H

#include "Camera.h"
#include "Vector3.h"
#include <vector>
#include <tuple>

using namespace std;

namespace Wrench
{
	class RailCamera : public Camera
	{
	protected:
		bool running;
		float railProgress;
		unsigned int lastFrameTime;
		vector<tuple<Vector3, Vector3>> rail;

	public:
		RailCamera(const Vector3 &nEye, const Vector3 &nFocus);
		virtual void AddRailPoint(const Vector3 &eyePos, const Vector3 &focus);

		virtual void Play();
		virtual void Stop();

		virtual void Begin();

		tuple<Vector3, Vector3> GetRailPoint(int ID);
	};
}

#endif
