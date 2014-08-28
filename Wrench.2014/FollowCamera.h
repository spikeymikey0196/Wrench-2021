#ifndef FOLLOWCAMERA_H
#define FOLLOWCAMERA_H

#include "Camera.h"
#include "Node.h"

namespace Wrench
{
	class FollowCamera : public Camera
	{
	protected:
		float followDistance;
		float heightOffset;
		Node *target;
		Vector3 prevTargetPos;
		Vector3 prevOrientation;
		Vector3 targetOffset;

	public:
		FollowCamera();
		FollowCamera(Node *nTarget, float nFollowDistance, float nHeightOffset, const Vector3 &nTargetOffset);

		void SetTarget(Node *nTarget);
		float FollowDistance();
		void SetFollowDistance(float nFollowDistance);

		virtual void Begin();
		virtual Matrix GetMatrix();
	};
}

#endif
