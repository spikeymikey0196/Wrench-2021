#include "Matrix.h"
#include <cmath>

using namespace std;

namespace Wrench
{
	Matrix::Matrix()
	{
		for(int a = 0; a < 16; a++)
			m[a] = 0;
	};

	Matrix::Matrix(float m11, float m12, float m13, float m14, float m21, float m22, float m23, float m24, float m31, float m32, float m33, float m34, float m41, float m42, float m43, float m44)
	{
		M11 = m11;
		M12 = m12;
		M13 = m13;
		M14 = m14;

		M21 = m21;
		M22 = m22;
		M23 = m23;
		M24 = m24;

		M31 = m31;
		M32 = m32;
		M33 = m33;
		M34 = m34;

		M41 = m41;
		M42 = m42;
		M43 = m43;
		M44 = m44;
	};

	Matrix Matrix::Identity()
	{
		Matrix matrix = Matrix();
		matrix.M11 = 1.0f;
		matrix.M22 = 1.0f;
		matrix.M33 = 1.0f;
		matrix.M44 = 1.0f;

		return matrix;
	};

	Vector3 Matrix::Backward()
	{
		return Vector3(M31, M32, M33);
	};

	void Matrix::Backward(const Vector3 &setVector)
	{
		M31 = setVector.x;
		M32 = setVector.y;
		M33 = setVector.z;
	};

	Vector3 Matrix::Up()
	{
		return Vector3(M21, M22, M23);
	};

	void Matrix::Up(const Vector3 &setVector)
	{
		M21 = setVector.x;
		M22 = setVector.y;
		M23 = setVector.z;
	};

	Vector3 Matrix::Down()
	{
		return Vector3(-M21, -M22, -M23);
	};

	void Matrix::Down(const Vector3 &setVector)
	{
		M21 = -setVector.x;
		M22 = -setVector.y;
		M23 = -setVector.z;
	};

	Vector3 Matrix::Forward()
	{
		return Vector3(-M31, -M32, -M33);
	};

	void Matrix::Forward(const Vector3 &setVector)
	{
		M31 = -setVector.x;
		M32 = -setVector.y;
		M33 = -setVector.z;
	};

	Vector3 Matrix::Left()
	{
		return Vector3(-M11, -M12, -M13);
	};

	void Matrix::Left(const Vector3 &setVector)
	{
		M11 = -setVector.x;
		M12 = -setVector.y;
		M13 = -setVector.z;
	};

	Vector3 Matrix::Right()
	{
		return Vector3(M11, M12, M13);
	};

	void Matrix::Right(const Vector3 &setVector)
	{
		M11 = setVector.x;
		M12 = setVector.y;
		M13 = setVector.z;
	};

	Vector3 Matrix::Translation()
	{
		return Vector3(M41, M42, M43);
	};

	void Matrix::Translation(const Vector3 &setVector)
	{
		M41 = setVector.x;
		M42 = setVector.y;
		M43 = setVector.z;
	};

	Matrix Matrix::Add(const Matrix &m1, const Matrix &m2)
	{
		Matrix mResult;

		mResult.M11 = m1.M11 + m2.M11;
		mResult.M12 = m1.M12 + m2.M12;
		mResult.M13 = m1.M13 + m2.M13;
		mResult.M14 = m1.M14 + m2.M14;
		mResult.M21 = m1.M21 + m2.M21;
		mResult.M22 = m1.M22 + m2.M22;
		mResult.M23 = m1.M23 + m2.M23;
		mResult.M24 = m1.M24 + m2.M24;
		mResult.M31 = m1.M31 + m2.M31;
		mResult.M32 = m1.M32 + m2.M32;
		mResult.M33 = m1.M33 + m2.M33;
		mResult.M34 = m1.M34 + m2.M34;
		mResult.M41 = m1.M41 + m2.M41;
		mResult.M42 = m1.M42 + m2.M42;
		mResult.M43 = m1.M43 + m2.M43;
		mResult.M44 = m1.M44 + m2.M44;

		return mResult;
	};

	Matrix Matrix::CreateFromAxisAngle(const Vector3 &axis, float angle)
	{
		Matrix matrix;

		float x = axis.x;
		float y = axis.y;
		float z = axis.z;
		float num2 = sin(angle);
		float num = cos(angle);
		float num11 = x * x;
		float num10 = y * y;
		float num9 = z * z;
		float num8 = x * y;
		float num7 = x * z;
		float num6 = y * z;

		matrix.M11 = num11 + (num * (1.0f - num11));
		matrix.M12 = (num8 - (num * num8)) + (num2 * z);
		matrix.M13 = (num7 - (num * num7)) - (num2 * y);
		matrix.M14 = 0.0f;
		matrix.M21 = (num8 - (num * num8)) - (num2 * z);
		matrix.M22 = num10 + (num * (1.0f - num10));
		matrix.M23 = (num6 - (num * num6)) + (num2 * x);
		matrix.M24 = 0.0f;
		matrix.M31 = (num7 - (num * num7)) + (num2 * y);
		matrix.M32 = (num6 - (num * num6)) - (num2 * x);
		matrix.M33 = num9 + (num * (1.0f - num9));
		matrix.M34 = 0.0f;
		matrix.M41 = 0.0f;
		matrix.M42 = 0.0f;
		matrix.M43 = 0.0f;
		matrix.M44 = 1.0f;

		return matrix;
	};

	Matrix Matrix::CreateFromQuaternion(const Quaternion &quaternion)
	{
		Matrix matrix;
		float num9 = quaternion.x * quaternion.x;
		float num8 = quaternion.y * quaternion.y;
		float num7 = quaternion.z * quaternion.z;
		float num6 = quaternion.x * quaternion.y;
		float num5 = quaternion.z * quaternion.w;
		float num4 = quaternion.z * quaternion.x;
		float num3 = quaternion.y * quaternion.w;
		float num2 = quaternion.y * quaternion.z;
		float num = quaternion.x * quaternion.w;
		matrix.M11 = 1.0f - (2.0f * (num8 + num7));
		matrix.M12 = 2.0f * (num6 + num5);
		matrix.M13 = 2.0f * (num4 - num3);
		matrix.M14 = 0.0f;
		matrix.M21 = 2.0f * (num6 - num5);
		matrix.M22 = 1.0f - (2.0f * (num7 + num9));
		matrix.M23 = 2.0f * (num2 + num);
		matrix.M24 = 0.0f;
		matrix.M31 = 2.0f * (num4 + num3);
		matrix.M32 = 2.0f * (num2 - num);
		matrix.M33 = 1.0f - (2.0f * (num8 + num9));
		matrix.M34 = 0.0f;
		matrix.M41 = 0.0f;
		matrix.M42 = 0.0f;
		matrix.M43 = 0.0f;
		matrix.M44 = 1.0f;
		return matrix;
	};

	Matrix Matrix::CreateFromYawPitchRoll(float pitch, float yaw, float roll)
	{
		return Matrix::CreateFromQuaternion(Quaternion::CreateFromYawPitchRoll(pitch, yaw, roll));
	};

	Matrix Matrix::CreateFromYawPitchRoll(const Vector3 &orientation)
	{
		return CreateFromYawPitchRoll(orientation.x, orientation.y, orientation.z);
	};

	Matrix Matrix::CreateLookAt(const Vector3 &cameraPosition, const Vector3 &cameraTarget, const Vector3 &cameraUpVector)
	{
		Vector3 vector3_1 = Vector3::Normalize((Vector3)cameraPosition - (Vector3)cameraTarget);
		Vector3 vector3_2 = Vector3::Normalize(Vector3::Cross(cameraUpVector, vector3_1));
		Vector3 vector1 = Vector3::Cross(vector3_1, vector3_2);
		Matrix matrix;
		matrix.M11 = vector3_2.x;
		matrix.M12 = vector1.x;
		matrix.M13 = vector3_1.x;
		matrix.M14 = 0.0f;
		matrix.M21 = vector3_2.y;
		matrix.M22 = vector1.y;
		matrix.M23 = vector3_1.y;
		matrix.M24 = 0.0f;
		matrix.M31 = vector3_2.z;
		matrix.M32 = vector1.z;
		matrix.M33 = vector3_1.z;
		matrix.M34 = 0.0f;
		matrix.M41 = -Vector3::Dot(vector3_2, cameraPosition);
		matrix.M42 = -Vector3::Dot(vector1, cameraPosition);
		matrix.M43 = -Vector3::Dot(vector3_1, cameraPosition);
		matrix.M44 = 1.0f;
		return matrix;
	};

	Matrix Matrix::CreateOrthographic(float width, float height, float zNearPlane, float zFarPlane)
	{
		Matrix result;

		result.M11 = 2.0f / width;
		result.M12 = result.M13 = result.M14 = 0.0f;
		result.M22 = 2.0f / height;
		result.M21 = result.M23 = result.M24 = 0.0f;
		result.M33 = 1.0f / (zNearPlane - zFarPlane);
		result.M31 = result.M32 = result.M34 = 0.0f;
		result.M41 = result.M42 = 0.0f;
		result.M43 = zNearPlane / (zNearPlane - zFarPlane);
		result.M44 = 1.0f;

		return result;
	};

	Matrix Matrix::CreateOrthographicOffCenter(float left, float right, float bottom, float top, float zNearPlane, float zFarPlane)
	{
		Matrix result;

		result.M11 = (2.0f / (right - left));
		result.M12 = 0.0f;
		result.M13 = 0.0f;
		result.M14 = 0.0f;
		result.M21 = 0.0f;
		result.M22 = (2.0f / (top - bottom));
		result.M23 = 0.0f;
		result.M24 = 0.0f;
		result.M31 = 0.0f;
		result.M32 = 0.0f;
		result.M33 = (1.0f / (zNearPlane - zFarPlane));
		result.M34 = 0.0f;
		result.M41 = ((left + right) / (left - right));
		result.M42 = ((top + bottom) / (bottom - top));
		result.M43 = (zNearPlane / (zNearPlane - zFarPlane));
		result.M44 = 1.0f;

		return result;
	};

	Matrix Matrix::CreatePerspective(float width, float height, float nearPlaneDistance, float farPlaneDistance)
	{
		Matrix matrix;


		matrix.M11 = (2.0f * nearPlaneDistance) / width;
		matrix.M12 = matrix.M13 = matrix.M14 = 0.0f;
		matrix.M22 = (2.0f * nearPlaneDistance) / height;
		matrix.M21 = matrix.M23 = matrix.M24 = 0.0f;
		matrix.M33 = farPlaneDistance / (nearPlaneDistance - farPlaneDistance);
		matrix.M31 = matrix.M32 = 0.0f;
		matrix.M34 = -1.0f;
		matrix.M41 = matrix.M42 = matrix.M44 = 0.0f;
		matrix.M43 = (nearPlaneDistance * farPlaneDistance) / (nearPlaneDistance - farPlaneDistance);
		return matrix;
	};

	Matrix Matrix::CreatePerspectiveFieldOfView(float fieldOfView, float aspectRatio, float nearPlaneDistance, float farPlaneDistance)
	{
		Matrix matrix;

		float num = 1.0f / (tan((fieldOfView * 0.5f)));
		float num9 = num / aspectRatio;
		matrix.M11 = num9;
		matrix.M12 = matrix.M13 = matrix.M14 = 0.0f;
		matrix.M22 = num;
		matrix.M21 = matrix.M23 = matrix.M24 = 0.0f;
		matrix.M31 = matrix.M32 = 0.0f;
		matrix.M33 = farPlaneDistance / (nearPlaneDistance - farPlaneDistance);
		matrix.M34 = -1.0f;
		matrix.M41 = matrix.M42 = matrix.M44 = 0.0f;
		matrix.M43 = (nearPlaneDistance * farPlaneDistance) / (nearPlaneDistance - farPlaneDistance);
		return matrix;
	};

	Matrix Matrix::CreatePerspectiveOffCenter(float left, float right, float bottom, float top, float nearPlaneDistance, float farPlaneDistance)
	{
		Matrix matrix;
		matrix.M11 = (2.0f * nearPlaneDistance) / (right - left);
		matrix.M12 = matrix.M13 = matrix.M14 = 0.0f;
		matrix.M22 = (2.0f * nearPlaneDistance) / (top - bottom);
		matrix.M21 = matrix.M23 = matrix.M24 = 0.0f;
		matrix.M31 = (left + right) / (right - left);
		matrix.M32 = (top + bottom) / (top - bottom);
		matrix.M33 = farPlaneDistance / (nearPlaneDistance - farPlaneDistance);
		matrix.M34 = -1.0f;
		matrix.M43 = (nearPlaneDistance * farPlaneDistance) / (nearPlaneDistance - farPlaneDistance);
		matrix.M41 = matrix.M42 = matrix.M44 = 0.0f;
		return matrix;
	};

	Matrix Matrix::CreateRotationX(float radians)
	{
		Matrix returnMatrix = Matrix::Identity();

		float val1 = cos(radians);
		float val2 = sin(radians);

		returnMatrix.M22 = val1;
		returnMatrix.M23 = val2;
		returnMatrix.M32 = -val2;
		returnMatrix.M33 = val1;

		return returnMatrix;
	};

	Matrix Matrix::CreateRotationY(float radians)
	{
		Matrix returnMatrix = Matrix::Identity();

		float val1 = cos(radians);
		float val2 = sin(radians);

		returnMatrix.M11 = val1;
		returnMatrix.M13 = -val2;
		returnMatrix.M31 = val2;
		returnMatrix.M33 = val1;

		return returnMatrix;
	};

	Matrix Matrix::CreateRotationZ(float radians)
	{
		Matrix returnMatrix = Matrix::Identity();

		float val1 = cos(radians);
		float val2 = sin(radians);

		returnMatrix.M11 = val1;
		returnMatrix.M12 = val2;
		returnMatrix.M21 = -val2;
		returnMatrix.M22 = val1;

		return returnMatrix;
	};

	Matrix Matrix::CreateScale(float scale)
	{
		Matrix result;
		result.M11 = scale;
		result.M12 = 0.0f;
		result.M13 = 0.0f;
		result.M14 = 0.0f;
		result.M21 = 0.0f;
		result.M22 = scale;
		result.M23 = 0.0f;
		result.M24 = 0.0f;
		result.M31 = 0.0f;
		result.M32 = 0.0f;
		result.M33 = scale;
		result.M34 = 0.0f;
		result.M41 = 0.0f;
		result.M42 = 0.0f;
		result.M43 = 0.0f;
		result.M44 = 1.0f;
		return result;
	};

	Matrix Matrix::CreateScale(float x, float y, float z)
	{
		Matrix result;
		result.M11 = x;
		result.M12 = 0.0f;
		result.M13 = 0.0f;
		result.M14 = 0.0f;
		result.M21 = 0.0f;
		result.M22 = y;
		result.M23 = 0.0f;
		result.M24 = 0.0f;
		result.M31 = 0.0f;
		result.M32 = 0.0f;
		result.M33 = z;
		result.M34 = 0.0f;
		result.M41 = 0.0f;
		result.M42 = 0.0f;
		result.M43 = 0.0f;
		result.M44 = 1.0f;
		return result;
	};

	Matrix Matrix::CreateScale(const Vector3 &scale)
	{
		Matrix result;
		result.M11 = scale.x;
		result.M12 = 0.0f;
		result.M13 = 0.0f;
		result.M14 = 0.0f;
		result.M21 = 0.0f;
		result.M22 = scale.y;
		result.M23 = 0.0f;
		result.M24 = 0.0f;
		result.M31 = 0.0f;
		result.M32 = 0.0f;
		result.M33 = scale.z;
		result.M34 = 0.0f;
		result.M41 = 0.0f;
		result.M42 = 0.0f;
		result.M43 = 0.0f;
		result.M44 = 1.0f;
		return result;
	};

	Matrix Matrix::CreateTranslation(const Vector3 &position)
	{
		return Matrix::CreateTranslation(position.x, position.y, position.z);
	};

	Matrix Matrix::CreateTranslation(float x, float y, float z)
	{
		Matrix result;
		result.M11 = 1.0f;
		result.M12 = 0.0f;
		result.M13 = 0.0f;
		result.M14 = 0.0f;
		result.M21 = 0.0f;
		result.M22 = 1.0f;
		result.M23 = 0.0f;
		result.M24 = 0.0f;
		result.M31 = 0.0f;
		result.M32 = 0.0f;
		result.M33 = 1.0f;
		result.M34 = 0.0f;
		result.M41 = x;
		result.M42 = y;
		result.M43 = z;
		result.M44 = 1.0f;
		return result;
	};

	Matrix Matrix::CreateWorld(const Vector3 &position, const Vector3 &forward, const Vector3 &up)
	{
		Vector3 x, y, z;
		z = Vector3::Normalize(forward);
		x = Vector3::Cross(forward, up);
		y = Vector3::Cross(x, forward);
		x = Vector3::Normalize(x);
		y = Vector3::Normalize(y);

		Matrix result = Matrix();
		result.Right(x);
		result.Up(y);
		result.Forward(z);
		result.Translation(position);
		result.M44 = 1.0f;

		return result;
	};

	Matrix Matrix::Divide(const Matrix &m1, const Matrix &m2)
	{
		Matrix mResult;

		mResult.M11 = m1.M11 / m2.M11;
		mResult.M12 = m1.M12 / m2.M12;
		mResult.M13 = m1.M13 / m2.M13;
		mResult.M14 = m1.M14 / m2.M14;
		mResult.M21 = m1.M21 / m2.M21;
		mResult.M22 = m1.M22 / m2.M22;
		mResult.M23 = m1.M23 / m2.M23;
		mResult.M24 = m1.M24 / m2.M24;
		mResult.M31 = m1.M31 / m2.M31;
		mResult.M32 = m1.M32 / m2.M32;
		mResult.M33 = m1.M33 / m2.M33;
		mResult.M34 = m1.M34 / m2.M34;
		mResult.M41 = m1.M41 / m2.M41;
		mResult.M42 = m1.M42 / m2.M42;
		mResult.M43 = m1.M43 / m2.M43;
		mResult.M44 = m1.M44 / m2.M44;

		return mResult;
	};

	Matrix Matrix::Divide(const Matrix &m1, float divider)
	{
		Matrix mResult;

		divider = 1.0f / divider;

		mResult.M11 = m1.M11 / divider;
		mResult.M12 = m1.M12 / divider;
		mResult.M13 = m1.M13 / divider;
		mResult.M14 = m1.M14 / divider;
		mResult.M21 = m1.M21 / divider;
		mResult.M22 = m1.M22 / divider;
		mResult.M23 = m1.M23 / divider;
		mResult.M24 = m1.M24 / divider;
		mResult.M31 = m1.M31 / divider;
		mResult.M32 = m1.M32 / divider;
		mResult.M33 = m1.M33 / divider;
		mResult.M34 = m1.M34 / divider;
		mResult.M41 = m1.M41 / divider;
		mResult.M42 = m1.M42 / divider;
		mResult.M43 = m1.M43 / divider;
		mResult.M44 = m1.M44 / divider;

		return mResult;
	};

	Matrix Matrix::Invert(const Matrix &matrix)
	{
		Matrix result;

		float num1 = matrix.M11;
		float num2 = matrix.M12;
		float num3 = matrix.M13;
		float num4 = matrix.M14;
		float num5 = matrix.M21;
		float num6 = matrix.M22;
		float num7 = matrix.M23;
		float num8 = matrix.M24;
		float num9 = matrix.M31;
		float num10 = matrix.M32;
		float num11 = matrix.M33;
		float num12 = matrix.M34;
		float num13 = matrix.M41;
		float num14 = matrix.M42;
		float num15 = matrix.M43;
		float num16 = matrix.M44;
		float num17 = (num11 * num16 - num12 * num15);
		float num18 = (num10 * num16 - num12 * num14);
		float num19 = (num10 * num15 - num11 * num14);
		float num20 = (num9 * num16 - num12 * num13);
		float num21 = (num9 * num15 - num11 * num13);
		float num22 = (num9 * num14 - num10 * num13);
		float num23 = (num6 * num17 - num7 * num18 + num8 * num19);
		float num24 =  -(num5 * num17 - num7 * num20 + num8 * num21);
		float num25 = (num5 * num18 - num6 * num20 + num8 * num22);
		float num26 =  -(num5 * num19 - num6 * num21 + num7 * num22);
		float num27 = (1.0f / (num1 * num23 + num2 * num24 + num3 * num25 + num4 * num26));

		result.M11 = num23 * num27;
		result.M21 = num24 * num27;
		result.M31 = num25 * num27;
		result.M41 = num26 * num27;
		result.M12 =  -(num2 * num17 - num3 * num18 + num4 * num19) * num27;
		result.M22 = (num1 * num17 - num3 * num20 + num4 * num21) * num27;
		result.M32 =  -(num1 * num18 - num2 * num20 + num4 * num22) * num27;
		result.M42 = (num1 * num19 - num2 * num21 + num3 * num22) * num27;
		float num28 = (num7 * num16 - num8 * num15);
		float num29 = (num6 * num16 - num8 * num14);
		float num30 = (num6 * num15 - num7 * num14);
		float num31 = (num5 * num16 - num8 * num13);
		float num32 = (num5 * num15 - num7 * num13);
		float num33 = (num5 * num14 - num6 * num13);
		result.M13 = (num2 * num28 - num3 * num29 + num4 * num30) * num27;
		result.M23 =  -(num1 * num28 - num3 * num31 + num4 * num32) * num27;
		result.M33 = (num1 * num29 - num2 * num31 + num4 * num33) * num27;
		result.M43 =  -(num1 * num30 - num2 * num32 + num3 * num33) * num27;
		float num34 = (num7 * num12 - num8 * num11);
		float num35 = (num6 * num12 - num8 * num10);
		float num36 = (num6 * num11 - num7 * num10);
		float num37 = (num5 * num12 - num8 * num9);
		float num38 = (num5 * num11 - num7 * num9);
		float num39 = (num5 * num10 - num6 * num9);
		result.M14 =  -(num2 * num34 - num3 * num35 + num4 * num36) * num27;
		result.M24 = (num1 * num34 - num3 * num37 + num4 * num38) * num27;
		result.M34 =  -(num1 * num35 - num2 * num37 + num4 * num39) * num27;
		result.M44 = (num1 * num36 - num2 * num38 + num3 * num39) * num27;

		return result;
	};

	Matrix Matrix::Lerp(const Matrix &matrix1, const Matrix &matrix2, float amount)
	{
		Matrix result;

		result.M11 = matrix1.M11 + ((matrix2.M11 - matrix1.M11) * amount);
		result.M12 = matrix1.M12 + ((matrix2.M12 - matrix1.M12) * amount);
		result.M13 = matrix1.M13 + ((matrix2.M13 - matrix1.M13) * amount);
		result.M14 = matrix1.M14 + ((matrix2.M14 - matrix1.M14) * amount);
		result.M21 = matrix1.M21 + ((matrix2.M21 - matrix1.M21) * amount);
		result.M22 = matrix1.M22 + ((matrix2.M22 - matrix1.M22) * amount);
		result.M23 = matrix1.M23 + ((matrix2.M23 - matrix1.M23) * amount);
		result.M24 = matrix1.M24 + ((matrix2.M24 - matrix1.M24) * amount);
		result.M31 = matrix1.M31 + ((matrix2.M31 - matrix1.M31) * amount);
		result.M32 = matrix1.M32 + ((matrix2.M32 - matrix1.M32) * amount);
		result.M33 = matrix1.M33 + ((matrix2.M33 - matrix1.M33) * amount);
		result.M34 = matrix1.M34 + ((matrix2.M34 - matrix1.M34) * amount);
		result.M41 = matrix1.M41 + ((matrix2.M41 - matrix1.M41) * amount);
		result.M42 = matrix1.M42 + ((matrix2.M42 - matrix1.M42) * amount);
		result.M43 = matrix1.M43 + ((matrix2.M43 - matrix1.M43) * amount);
		result.M44 = matrix1.M44 + ((matrix2.M44 - matrix1.M44) * amount);

		return result;
	};

	Matrix Matrix::Multiply(const Matrix &matrix1, const Matrix &matrix2)
	{
		Matrix result;
		float m11 = (((matrix1.M11 * matrix2.M11) + (matrix1.M12 * matrix2.M21)) + (matrix1.M13 * matrix2.M31)) + (matrix1.M14 * matrix2.M41);
		float m12 = (((matrix1.M11 * matrix2.M12) + (matrix1.M12 * matrix2.M22)) + (matrix1.M13 * matrix2.M32)) + (matrix1.M14 * matrix2.M42);
		float m13 = (((matrix1.M11 * matrix2.M13) + (matrix1.M12 * matrix2.M23)) + (matrix1.M13 * matrix2.M33)) + (matrix1.M14 * matrix2.M43);
		float m14 = (((matrix1.M11 * matrix2.M14) + (matrix1.M12 * matrix2.M24)) + (matrix1.M13 * matrix2.M34)) + (matrix1.M14 * matrix2.M44);
		float m21 = (((matrix1.M21 * matrix2.M11) + (matrix1.M22 * matrix2.M21)) + (matrix1.M23 * matrix2.M31)) + (matrix1.M24 * matrix2.M41);
		float m22 = (((matrix1.M21 * matrix2.M12) + (matrix1.M22 * matrix2.M22)) + (matrix1.M23 * matrix2.M32)) + (matrix1.M24 * matrix2.M42);
		float m23 = (((matrix1.M21 * matrix2.M13) + (matrix1.M22 * matrix2.M23)) + (matrix1.M23 * matrix2.M33)) + (matrix1.M24 * matrix2.M43);
		float m24 = (((matrix1.M21 * matrix2.M14) + (matrix1.M22 * matrix2.M24)) + (matrix1.M23 * matrix2.M34)) + (matrix1.M24 * matrix2.M44);
		float m31 = (((matrix1.M31 * matrix2.M11) + (matrix1.M32 * matrix2.M21)) + (matrix1.M33 * matrix2.M31)) + (matrix1.M34 * matrix2.M41);
		float m32 = (((matrix1.M31 * matrix2.M12) + (matrix1.M32 * matrix2.M22)) + (matrix1.M33 * matrix2.M32)) + (matrix1.M34 * matrix2.M42);
		float m33 = (((matrix1.M31 * matrix2.M13) + (matrix1.M32 * matrix2.M23)) + (matrix1.M33 * matrix2.M33)) + (matrix1.M34 * matrix2.M43);
		float m34 = (((matrix1.M31 * matrix2.M14) + (matrix1.M32 * matrix2.M24)) + (matrix1.M33 * matrix2.M34)) + (matrix1.M34 * matrix2.M44);
		float m41 = (((matrix1.M41 * matrix2.M11) + (matrix1.M42 * matrix2.M21)) + (matrix1.M43 * matrix2.M31)) + (matrix1.M44 * matrix2.M41);
		float m42 = (((matrix1.M41 * matrix2.M12) + (matrix1.M42 * matrix2.M22)) + (matrix1.M43 * matrix2.M32)) + (matrix1.M44 * matrix2.M42);
		float m43 = (((matrix1.M41 * matrix2.M13) + (matrix1.M42 * matrix2.M23)) + (matrix1.M43 * matrix2.M33)) + (matrix1.M44 * matrix2.M43);
		float m44 = (((matrix1.M41 * matrix2.M14) + (matrix1.M42 * matrix2.M24)) + (matrix1.M43 * matrix2.M34)) + (matrix1.M44 * matrix2.M44);
		result.M11 = m11;
		result.M12 = m12;
		result.M13 = m13;
		result.M14 = m14;
		result.M21 = m21;
		result.M22 = m22;
		result.M23 = m23;
		result.M24 = m24;
		result.M31 = m31;
		result.M32 = m32;
		result.M33 = m33;
		result.M34 = m34;
		result.M41 = m41;
		result.M42 = m42;
		result.M43 = m43;
		result.M44 = m44;
		return result;
	};

	Matrix Matrix::Multiply(const Matrix &matrix, float factor)
	{
		Matrix result;

		result.M11 = matrix.M11 * factor;
		result.M12 = matrix.M12 * factor;
		result.M13 = matrix.M13 * factor;
		result.M14 = matrix.M14 * factor;
		result.M21 = matrix.M21 * factor;
		result.M22 = matrix.M22 * factor;
		result.M23 = matrix.M23 * factor;
		result.M24 = matrix.M24 * factor;
		result.M31 = matrix.M31 * factor;
		result.M32 = matrix.M32 * factor;
		result.M33 = matrix.M33 * factor;
		result.M34 = matrix.M34 * factor;
		result.M41 = matrix.M41 * factor;
		result.M42 = matrix.M42 * factor;
		result.M43 = matrix.M43 * factor;
		result.M44 = matrix.M44 * factor;

		return result;
	};

	Matrix Matrix::Negate(const Matrix &matrix)
	{
		Matrix mResult;

		mResult.M11 = -matrix.M11;
		mResult.M12 = -matrix.M12;
		mResult.M13 = -matrix.M13;
		mResult.M14 = -matrix.M14;
		mResult.M21 = -matrix.M21;
		mResult.M22 = -matrix.M22;
		mResult.M23 = -matrix.M23;
		mResult.M24 = -matrix.M24;
		mResult.M31 = -matrix.M31;
		mResult.M32 = -matrix.M32;
		mResult.M33 = -matrix.M33;
		mResult.M34 = -matrix.M34;
		mResult.M41 = -matrix.M41;
		mResult.M42 = -matrix.M42;
		mResult.M43 = -matrix.M43;
		mResult.M44 = -matrix.M44;

		return mResult;
	};

	Matrix Matrix::Subtract(const Matrix &m1, const Matrix &m2)
	{
		Matrix mResult;

		mResult.M11 = m1.M11 - m2.M11;
		mResult.M12 = m1.M12 - m2.M12;
		mResult.M13 = m1.M13 - m2.M13;
		mResult.M14 = m1.M14 - m2.M14;
		mResult.M21 = m1.M21 - m2.M21;
		mResult.M22 = m1.M22 - m2.M22;
		mResult.M23 = m1.M23 - m2.M23;
		mResult.M24 = m1.M24 - m2.M24;
		mResult.M31 = m1.M31 - m2.M31;
		mResult.M32 = m1.M32 - m2.M32;
		mResult.M33 = m1.M33 - m2.M33;
		mResult.M34 = m1.M34 - m2.M34;
		mResult.M41 = m1.M41 - m2.M41;
		mResult.M42 = m1.M42 - m2.M42;
		mResult.M43 = m1.M43 - m2.M43;
		mResult.M44 = m1.M44 - m2.M44;

		return mResult;
	};

	Matrix Matrix::Transpose(const Matrix &matrix)
	{
		Matrix result;

		result.M11 = matrix.M11;
		result.M12 = matrix.M21;
		result.M13 = matrix.M31;
		result.M14 = matrix.M41;

		result.M21 = matrix.M12;
		result.M22 = matrix.M22;
		result.M23 = matrix.M32;
		result.M24 = matrix.M42;

		result.M31 = matrix.M13;
		result.M32 = matrix.M23;
		result.M33 = matrix.M33;
		result.M34 = matrix.M43;

		result.M41 = matrix.M14;
		result.M42 = matrix.M24;
		result.M43 = matrix.M34;
		result.M44 = matrix.M44;

		return result;
	};

	Matrix Matrix::operator+(const Matrix &param)
	{
		return Matrix::Add(*this, param);
	};

	Matrix Matrix::operator/(const Matrix &param)
	{
		return Matrix::Divide(*this, param);
	};

	Matrix Matrix::operator/(float param)
	{
		return Matrix::Divide(*this, param);
	};

	bool Matrix::operator==(const Matrix &param)
	{
		for(int a = 0; a < 16; a++)
			if(this->m[a] != param.m[a])
				return false;

		return true;
	};

	bool Matrix::operator!=(const Matrix &param)
	{
		for(int a = 0; a < 16; a++)
			if(this->m[a] != param.m[a])
				return true;

		return false;
	};

	Matrix Matrix::operator*(const Matrix &param)
	{
		return Matrix::Multiply(*this, param);
	};

	Matrix Matrix::operator*(float param)
	{
		return Matrix::Multiply(*this, param);
	};

	Matrix Matrix::operator-(const Matrix &param)
	{
		return Matrix::Subtract(*this, param);
	};

	void Matrix::Replace(const Matrix &matrix)
	{
		float *f = ((Matrix)matrix).glData();

		for(int a = 0; a < 16; a++)
			m[a] = f[a];
	};
	
	float *Matrix::glData()
	{
		return m;
	};
}
