#ifndef RAILCAMERA_H
#define RAILCAMERA_H

#include "Camera.h"
#include "Vector3.h"
#include <vector>
#include <tuple>
#include <functional>

using namespace std;

namespace Wrench
{
	enum RailLoop
	{
		RAIL_ONCE	=	0,
		RAIL_LOOP	=	1,
	};

	class RailCamera : public Camera
	{
	protected:
		bool running;
		float railProgress;
		unsigned int lastFrameTime;
		int loopType;
		function<void(RailCamera*)> onFinish;
		vector<tuple<Vector3, Vector3>> rail;

	public:
		RailCamera(const Vector3 &nEye, const Vector3 &nFocus, int nLoopType);
		virtual void AddRailPoint(const Vector3 &eyePos, const Vector3 &focus);
		virtual void SetOnFinish(function<void(RailCamera*)> nOnFinish);

		virtual void Play();
		virtual void Stop();

		virtual void Begin();

		tuple<Vector3, Vector3> GetRailPoint(int ID);
	};
}

#endif
