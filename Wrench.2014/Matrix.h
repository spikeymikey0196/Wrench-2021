#ifndef Matrix_H
#define Matrix_H

#include "Vector3.h"
#include "Vector4.h"
#include "Quaternion.h"

namespace Wrench
{
	class Matrix
	{
	public:
		union
		{
			struct
			{
				float	M11, M12, M13, M14,
						M21, M22, M23, M24,
						M31, M32, M33, M34,
						M41, M42, M43, M44;
			};
			float m[16];
		};

	public:
		Matrix();
		Matrix(float m11, float m12, float m13, float m14, float m21, float m22, float m23, float m24, float m31, float m32, float m33, float m34, float m41, float m42, float m43, float m44);

		static Matrix Identity();

		Vector3 Backward();
		void Backward(const Vector3 &setVector);

		Vector3 Up();
		void Up(const Vector3 &setVector);

		Vector3 Down();
		void Down(const Vector3 &setVector);

		Vector3 Forward();
		void Forward(const Vector3 &setVector);

		Vector3 Left();
		void Left(const Vector3 &setVector);

		Vector3 Right();
		void Right(const Vector3 &setVector);

		Vector3 Translation();
		void Translation(const Vector3 &setVector);

		static Matrix Add(const Matrix &m1, const Matrix &m2);
		static Matrix CreateFromAxisAngle(const Vector3 &axis, float angle);
		static Matrix CreateFromQuaternion(const Quaternion &quaternion);
		static Matrix CreateFromYawPitchRoll(float pitch, float yaw, float roll);
		static Matrix CreateFromYawPitchRoll(const Vector3 &orientation);
		static Matrix CreateLookAt(const Vector3 &cameraPosition, const Vector3 &cameraTarget, const Vector3 &cameraUpVector);
		static Matrix CreateOrthographic(float width, float height, float zNearPlane, float zFarPlane);
		static Matrix CreateOrthographicOffCenter(float left, float right, float bottom, float top, float zNearPlane, float zFarPlane);
		static Matrix CreatePerspective(float width, float height, float nearPlaneDistance, float farPlaneDistance);
		static Matrix CreatePerspectiveFieldOfView(float fieldOfView, float aspectRatio, float nearPlaneDistance, float farPlaneDistance);
		static Matrix CreatePerspectiveOffCenter(float left, float right, float bottom, float top, float nearPlaneDistance, float farPlaneDistance);
		static Matrix CreateRotationX(float radians);
		static Matrix CreateRotationY(float radians);
		static Matrix CreateRotationZ(float radians);
		static Matrix CreateScale(float scale);
		static Matrix CreateScale(float x, float y, float z);
		static Matrix CreateScale(const Vector3 &scale);
		static Matrix CreateTranslation(const Vector3 &position);
		static Matrix CreateTranslation(float x, float y, float z);
		static Matrix CreateWorld(const Vector3 &position, const Vector3 &forward, const Vector3 &up);
		static Matrix Divide(const Matrix &m1, const Matrix &m2);
		static Matrix Divide(const Matrix &m1, float divider);
		static Matrix Invert(const Matrix &matrix);
		static Matrix Lerp(const Matrix &matrix1, const Matrix &matrix2, float amount);
		static Matrix Multiply(const Matrix &matrix1, const Matrix &matrix2);
		static Matrix Multiply(const Matrix &matrix, float factor);
		static Matrix Negate(const Matrix &matrix);
		static Matrix Subtract(const Matrix &m1, const Matrix &m2);
		static Matrix Transform(const Matrix &matrix, const Vector4 &rotation);
		static Matrix Transpose(const Matrix &matrix);

		Matrix operator+(const Matrix &param);
		Matrix operator/(const Matrix &param);
		Matrix operator/(float param);
		bool operator==(const Matrix &param);
		bool operator!=(const Matrix &param);
		Matrix operator*(const Matrix &param);
		Matrix operator*(float param);
		Matrix operator-(const Matrix &param);

		void Replace(const Matrix &matrix);

		float *glData();
	};
}

#endif
