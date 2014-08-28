#include "FollowCamera.h"

namespace Wrench
{
	FollowCamera::FollowCamera()
	{
		followDistance = 10.0f;
		target = NULL;
		prevTargetPos = Vector3::Zero();
		prevOrientation = Vector3::Zero();
	};

	FollowCamera::FollowCamera(Node *nTarget, float nFollowDistance, float nHeightOffset, const Vector3 &nTargetOffset)
		: Camera(Vector3(0, 0, 10), Vector3(0, 0, 0), Vector3(0,1,0))
	{
		target = nTarget;
		followDistance = nFollowDistance;
		heightOffset = nHeightOffset;
		targetOffset = nTargetOffset;

		if (target)
		{
			prevTargetPos = target->GetTransform()->Position();
			prevOrientation = target->GetTransform()->Orientation();
			SetFocus(prevTargetPos + targetOffset);
			SetEye(prevTargetPos + target->GetTransform()->GetMatrix().Backward().Normalize() * followDistance + Vector3(0, heightOffset, 0));
		}
	};

	void FollowCamera::SetTarget(Node *nTarget)
	{
		target = nTarget;
	};

	float FollowCamera::FollowDistance()
	{
		return followDistance;
	};

	void FollowCamera::SetFollowDistance(float nFollowDistance)
	{
		followDistance = nFollowDistance;
	};

	void FollowCamera::Begin()
	{
		if (target)
		{
			Vector3 tPos = target->GetTransform()->Position();
			Vector3 tOri = target->GetTransform()->Orientation();

			if (!(tPos == prevTargetPos) || !(tOri == prevOrientation))
			{
				prevTargetPos = tPos;
				prevOrientation = tOri;
				prevOrientation = target->GetTransform()->Orientation();
				SetFocus(prevTargetPos + targetOffset);
				SetEye(tPos + target->GetTransform()->GetMatrix().Backward().Normalize() * followDistance + Vector3(0, heightOffset, 0));
			}
		}

		Camera::Begin();
	};

	Matrix FollowCamera::GetMatrix()
	{
		if (target)
		{
			Vector3 tPos = target->GetTransform()->Position();
			Vector3 tOri = target->GetTransform()->Orientation();

			if (!(tPos == prevTargetPos) || !(tOri == prevOrientation))
			{
				prevTargetPos = tPos;
				prevOrientation = tOri;
				SetFocus(prevTargetPos + targetOffset);
				SetEye(tPos + target->GetTransform()->GetMatrix().Backward().Normalize() * followDistance + Vector3(0, heightOffset, 0));
			}
		}

		return Camera::GetMatrix();
	};

};
