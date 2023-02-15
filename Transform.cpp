#include "pch.h"
#include "include/Transform.h"
#include "include/ConstantValues.h"

namespace pxd
{
	Matrix3D MakeRotationX(float angle)
	{
		double rad = DegToRad(angle);
		float cosine = cos(rad);
		float sine = sin(rad);

		return Matrix3D(
			1.0f, 0.0f,    0.0f,
			0.0f, cosine, -sine,
			0.0f, sine,  cosine
		);
	}

	Matrix3D MakeRotationY(float angle)
	{
		double rad = DegToRad(angle);
		float cosine = cos(rad);
		float sine = sin(rad);

		return Matrix3D(
			cosine, 0.0f, sine,
			  0.0f, 1.0f, 0.0f,
			 -sine, 0.0f, cosine
		);
	}

	Matrix3D MakeRotationZ(float angle)
	{
		double rad = DegToRad(angle);
		float cosine = cos(rad);
		float sine = sin(rad);

		return Matrix3D(
			cosine,  -sine, 0.0f,
			  sine, cosine, 0.0f,
			  0.0f,   0.0f, 1.0f
		);
	}

	Matrix3D MakeRotation(const Vector3D& axis, float angle)
	{
		double rad = DegToRad(angle);
		float sine = sin(rad);
		float cosine = cos(rad);
		float oneMinCos = 1.0f - cosine;

		float x = axis.x * oneMinCos;
		float y = axis.y * oneMinCos;
		float z = axis.z * oneMinCos;

		float axay = x * axis.y;
		float axaz = x * axis.z;
		float ayaz = y * axis.z;

		return Matrix3D(
			 cosine + x * axis.x, axay - sine * axis.z, axaz + sine * axis.y,
			axay + sine * axis.z,  cosine + y * axis.y, ayaz - sine * axis.x,
			axaz - sine * axis.y, ayaz + sine * axis.x,  cosine + z * axis.z
		);
	}

	Matrix3D MakeReflection(const Vector3D& axis)
	{
		float x = axis.x * -2.0f;
		float y = axis.y * -2.0f;
		float z = axis.z * -2.0f;

		float axay = x * axis.y;
		float axaz = x * axis.z;
		float ayaz = y * axis.z;

		return Matrix3D(
			x * axis.x + 1.0f, axay, axaz,
			axay, y * axis.y + 1.0f, ayaz,
			axaz, ayaz, z * axis.z + 1.0f
		);
	}

	Matrix3D MakeInvolution(const Vector3D& axis)
	{
		float x = axis.x * 2.0f;
		float y = axis.y * 2.0f;
		float z = axis.z * 2.0f;

		float axay = x * axis.y;
		float axaz = x * axis.z;
		float ayaz = y * axis.z;

		return Matrix3D(
			x * axis.x - 1.0f, axay, axaz,
			axay, y * axis.y - 1.0f, ayaz,
			axaz, ayaz, z * axis.z - 1.0f
		);
	}
}