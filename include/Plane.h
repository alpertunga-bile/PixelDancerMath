#pragma once

#include "Point3D.h"

struct Plane
{
	// Rule of 5
	PXDMATH_API Plane() = default; // default constructor
	PXDMATH_API Plane(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {}; // special constructor
	PXDMATH_API Plane(const Vector3D& n, float d) : x(n.x), y(n.y), z(n.z), w(d) {} // special constructor
	PXDMATH_API Plane(const Plane& other) = default; // copy constructor
	PXDMATH_API Plane(Plane&& other) = default; // move constructor
	PXDMATH_API Plane& operator=(const Plane& other) = default; // move assignment
	PXDMATH_API ~Plane() = default; // deconstructor

	PXDMATH_API inline const Vector3D GetNormal() const { return Vector3D(x, y, z); }

	float x, y, z, w;
};

inline float Dot(const Plane& f, const Vector3D& v)
{
	return (f.x * v.x + f.y * v.y + f.z * v.z);
}

inline float Dot(const Plane& f, const Point3D& p)
{
	return (f.x * p.x + f.y * p.y + f.z * p.z + f.w);
}
