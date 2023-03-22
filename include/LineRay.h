#pragma once

#include "Transform4D.h"

struct Line
{
	// Rule of 5
	PXDMATH_API Line() = default; // default constructor
	PXDMATH_API Line(float vx, float vy, float vz, float mx, float my, float mz) : direction(vx, vy, vz), moment(mx, my, mz) {}; // special constructor
	PXDMATH_API Line(const Vector3D& v, const Vector3D& m) : direction(v), moment(m) {}
	PXDMATH_API Line(const Line& other) = default; // copy constructor
	PXDMATH_API Line(Line&& other) = default; // move constructor
	PXDMATH_API Line& operator=(const Line& other) = default; // move assignment
	PXDMATH_API ~Line() = default; // deconstructor

	Vector3D direction;
	Vector3D moment;
};

Line PXDMATH_API Transform(const Line& line, const Transform4D& h);
double PXDMATH_API DistancePointLine(const Point3D& p, const Point3D& start, const Vector3D& dir);
double PXDMATH_API DistanceLineLine(const Point3D& p1, const Vector3D& dir1, const Point3D& p2, const Vector3D& dir2);
