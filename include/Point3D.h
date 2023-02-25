#pragma once

#include "Vector3D.h"

struct Point3D : Vector3D
{
	Point3D() = default;
	Point3D(__m256d newVector) : Vector3D(newVector) {}
	Point3D(double a, double b, double c) : Vector3D(a, b, c) {}
};

inline Point3D operator+(const Point3D& a, const Vector3D& b)
{
	return Point3D(_mm256_add_pd(a._vector, b._vector));
}

inline Vector3D operator-(const Point3D& a, const Point3D& b)
{
	return Vector3D(_mm256_sub_pd(a._vector, b._vector));
}
