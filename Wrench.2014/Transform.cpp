#include "Transform.h"
#include "Utils.h"

#include <string>

using namespace std;

namespace Wrench
{
	Transform::Transform()
	{
		position = Vector3::Zero();
		orientation = Vector3::Zero();
		scale = Vector3(1, 1, 1);

		needsRecalc = true;
	};

	Transform::Transform(const Vector3 &nPosition, const Vector3 &nOrientation, const Vector3 &nScale)
	{
		position = nPosition;
		orientation = nOrientation;
		scale = nScale;

		needsRecalc = true;
	};

	Transform::Transform(const Vector3 &nPosition, const Vector3 &nOrientation, float nScale)
	{
		position = nPosition;
		orientation = nOrientation;
		scale = Vector3(nScale, nScale, nScale);

		needsRecalc = true;
	};

	Transform::Transform(TiXmlElement *entry)
		: Transform()
	{
		XmlLoop(entry, it)
		{
			string valueStr = it->ValueStr();

			if (!valueStr.compare("Position")) position = Vector3(it);
			if (!valueStr.compare("Orientation")) orientation = Vector3(it);
			if (!valueStr.compare("Scale")) scale = Vector3(it);
		}
	}

	void Transform::SetPosition(const Vector3 &nPosition)
	{
		position = nPosition;
		needsRecalc = true;
	};

	Vector3 Transform::Position()
	{
		return position;
	};

	void Transform::SetOrientation(const Vector3 &nOrientation)
	{
		orientation = nOrientation;
		needsRecalc = true;
	};

	Vector3 Transform::Orientation()
	{
		return orientation;
	};

	void Transform::SetScale(const Vector3 &nScale)
	{
		scale = nScale;
		needsRecalc = true;
	};

	void Transform::SetScale(float nScale)
	{
		scale = Vector3(nScale, nScale, nScale);
		needsRecalc = true;
	};

	Vector3 Transform::Scale()
	{
		return scale;
	};

	void Transform::Recalculate()
	{
		matrix = Matrix::CreateFromYawPitchRoll(orientation) * Matrix::CreateScale(scale) * Matrix::CreateTranslation(position);
		needsRecalc = false;
	};

	Matrix Transform::GetMatrix()
	{
		if (needsRecalc)
			Recalculate();
		return matrix;
	}
}