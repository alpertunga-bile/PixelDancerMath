#pragma once

#include "Vector4D.h"

// column based matrix
struct Matrix4D
{
public:
	// Rule of 5
	PXDMATH_API Matrix4D() = default; // default constructor
	PXDMATH_API Matrix4D(float n00, float n01, float n02, float n03, float n10, float n11, float n12, float n13, float n20, float n21, float n22, float n23, float n30, float n31, float n32, float n33); // special constructor
	PXDMATH_API Matrix4D(const Vector4D& a, const Vector4D& b, const Vector4D& c, const Vector4D& d); // special constructor
	PXDMATH_API Matrix4D(const Matrix4D& other) = default; // copy constructor
	PXDMATH_API Matrix4D(Matrix4D&& other) = default; // move constructor
	PXDMATH_API Matrix4D& operator=(const Matrix4D& other) = default; // move assignment
	PXDMATH_API ~Matrix4D() = default; // deconstructor

	PXDMATH_API void Print(const char* name);

	PXDMATH_API float& operator()(int i, int j)
	{
		return (n[j][i]);
	}

	PXDMATH_API const float& operator()(int i, int j) const
	{
		return (n[j][i]);
	}

	// access the jth column
	PXDMATH_API Vector4D& operator[] (int j)
	{
		return (*reinterpret_cast<Vector4D*>(n[j]));
	}

	// access the jth column
	PXDMATH_API const Vector4D& operator[](int j) const
	{
		return (*reinterpret_cast<const Vector4D*>(n[j]));
	}

	/*
	PXDMATH_API Matrix4D& operator*=(float s);
	PXDMATH_API Matrix4D& operator/=(float s);
	PXDMATH_API Matrix4D& operator+=(const Matrix4D& v);
	PXDMATH_API Matrix4D& operator-=(const Matrix4D& v);
	*/

private:
	float n[4][4];
};

inline Matrix4D operator+(Matrix4D mA, Matrix4D mB)
{
	Vector4D a = mA[0] + mB[0];
	Vector4D b = mA[1] + mB[1];
	Vector4D c = mA[2] + mB[2];
	Vector4D d = mA[3] + mB[3];

	return Matrix4D(a, b, c, d);
}

inline Matrix4D operator-(Matrix4D mA, Matrix4D mB)
{
	Vector4D a = mA[0] - mB[0];
	Vector4D b = mA[1] - mB[1];
	Vector4D c = mA[2] - mB[2];
	Vector4D d = mA[3] - mB[3];

	return Matrix4D(a, b, c, d);
}

inline Matrix4D operator*(Matrix4D matrix, float scalar)
{
	Vector4D a = matrix[0] * scalar;
	Vector4D b = matrix[1] * scalar;
	Vector4D c = matrix[2] * scalar;
	Vector4D d = matrix[3] * scalar;

	return Matrix4D(a, b, c, d);
}

Matrix4D operator*(const Matrix4D& a, const Matrix4D b)
{
	return Matrix4D(
		a(0, 0) * b(0, 0) + a(0, 1) * b(1, 0) + a(0, 2) * b(2, 0) + a(0, 3) * b(3, 0),
		a(0, 0) * b(0, 1) + a(0, 1) * b(1, 1) + a(0, 2) * b(2, 1) + a(0, 3) * b(3, 1),
		a(0, 0) * b(0, 2) + a(0, 1) * b(1, 2) + a(0, 2) * b(2, 2) + a(0, 3) * b(3, 2),
		a(0, 0) * b(0, 3) + a(0, 1) * b(1, 3) + a(0, 2) * b(2, 3) + a(0, 3) * b(3, 3),

		a(1, 0) * b(0, 0) + a(1, 1) * b(1, 0) + a(1, 2) * b(2, 0) + a(1, 3) * b(3, 0),
		a(1, 0) * b(0, 1) + a(1, 1) * b(1, 1) + a(1, 2) * b(2, 1) + a(1, 3) * b(3, 1),
		a(1, 0) * b(0, 2) + a(1, 1) * b(1, 2) + a(1, 2) * b(2, 2) + a(1, 3) * b(3, 2),
		a(1, 0) * b(0, 3) + a(1, 1) * b(1, 3) + a(1, 2) * b(2, 3) + a(1, 3) * b(3, 3),

		a(2, 0) * b(0, 0) + a(2, 1) * b(1, 0) + a(2, 2) * b(2, 0) + a(2, 3) * b(3, 0),
		a(2, 0) * b(0, 1) + a(2, 1) * b(1, 1) + a(2, 2) * b(2, 1) + a(2, 3) * b(3, 1),
		a(2, 0) * b(0, 2) + a(2, 1) * b(1, 2) + a(2, 2) * b(2, 2) + a(2, 3) * b(3, 2),
		a(2, 0) * b(0, 3) + a(2, 1) * b(1, 3) + a(2, 2) * b(2, 3) + a(2, 3) * b(3, 3),

		a(3, 0) * b(0, 0) + a(3, 1) * b(1, 0) + a(3, 2) * b(2, 0) + a(3, 3) * b(3, 0),
		a(3, 0) * b(0, 1) + a(3, 1) * b(1, 1) + a(3, 2) * b(2, 1) + a(3, 3) * b(3, 1),
		a(3, 0) * b(0, 2) + a(3, 1) * b(1, 2) + a(3, 2) * b(2, 2) + a(3, 3) * b(3, 2),
		a(3, 0) * b(0, 3) + a(3, 1) * b(1, 3) + a(3, 2) * b(2, 3) + a(3, 3) * b(3, 3)
	);
}

Vector4D operator*(const Matrix4D& m, const Vector4D& v)
{
	return Vector4D(
		m(0, 0) * v.x + m(0, 1) * v.y + m(0, 2) * v.z + m(0, 3) * v.w,
		m(1, 0) * v.x + m(1, 1) * v.y + m(1, 2) * v.z + m(1, 3) * v.w,
		m(2, 0) * v.x + m(2, 1) * v.y + m(2, 2) * v.z + m(2, 3) * v.w,
		m(3, 0) * v.x + m(3, 1) * v.y + m(3, 2) * v.z + m(3, 3) * v.w
	);
}
