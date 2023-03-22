#pragma once

#include "Transform4D.h"

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

inline Plane operator*(const Plane& f, const Transform4D& h)
{
	return Plane(
		f.x * h(0, 0) + f.y * h(1, 0) + f.z * h(2, 0),
		f.x * h(0, 1) + f.y * h(1, 1) + f.z * h(2, 1),
		f.x * h(0, 2) + f.y * h(1, 2) + f.z * h(2, 2),
		f.x * h(0, 3) + f.y * h(1, 3) + f.z * h(2, 3) + f.w
	);
}

inline float Dot(const Plane& f, const Vector3D& v)
{
	return (f.x * v.x + f.y * v.y + f.z * v.z);
}

inline float Dot(const Plane& f, const Point3D& p)
{
	return (f.x * p.x + f.y * p.y + f.z * p.z + f.w);
}

bool PXDMATH_API IntersectLinePlane(const Point3D& p, const Vector3D& dir, const Plane& f, Point3D& q);
Transform4D PXDMATH_API MakeReflection(const Plane& f);
bool PXDMATH_API IntersectThreePlanes(const Plane& f1, const Plane& f2, const Plane& f3, Point3D& p);
bool PXDMATH_API IntersectTwoPlanes(const Plane& f1, const Plane& f2, Point3D& p, Vector3D& v);