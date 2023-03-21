#pragma once

#include "Point3D.h"

double PXDMATH_API DistancePointLine(const Point3D& p, const Point3D& start, const Vector3D& dir);
double PXDMATH_API DistanceLineLine(const Point3D& p1, const Vector3D& dir1, const Point3D& p2, const Vector3D& dir2);
