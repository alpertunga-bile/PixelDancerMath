#pragma once

#include "Matrix3D.h"

struct Quaternion
{
	PXDMATH_API Quaternion() = default; // default constructor
	PXDMATH_API Quaternion(double a, double b, double c, double d);
	PXDMATH_API Quaternion(const Vector3D& _v, double s);
	PXDMATH_API Quaternion(const Quaternion& other) = default; // copy constructor
	PXDMATH_API Quaternion(Quaternion&& other) = default; // move constructor
	PXDMATH_API Quaternion& operator=(const Quaternion& other) = default; // move assignment
	PXDMATH_API ~Quaternion() = default; // deconstructor

	Matrix3D GetRotationMatrix();
	void SetRotationMatrix(const Matrix3D& m);

	Vector3D v;
	double w = 0.0;
};

inline Quaternion operator*(const Quaternion& q1, const Quaternion& q2)
{
	return Quaternion(
		Cross(q1.v, q2.v) + q2.v * q1.w + q1.v * q2.w, 
		q1.w * q2.w - Dot(q1.v, q2.v)
	);
}