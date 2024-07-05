#pragma once

#include "Vector3D.h"

struct Point3D;
struct Transform4D;

struct Line
{
  // Rule of 5
  Line() = default; // default constructor
  Line(double vx, double vy, double vz, double mx, double my, double mz)
    : direction(vx, vy, vz)
    , moment(mx, my, mz){}; // special constructor
  Line(const Vector3D& v, const Vector3D& m)
    : direction(v)
    , moment(m)
  {
  }
  Line(const Line& other)            = default; // copy constructor
  Line(Line&& other)                 = default; // move constructor
  Line& operator=(const Line& other) = default; // move assignment
  ~Line()                            = default; // deconstructor

  Vector3D direction;
  Vector3D moment;
};

Line
Transform(const Line& line, const Transform4D& h);

double
DistancePointLine(const Point3D& p, const Point3D& start, const Vector3D& dir);

double
DistanceLineLine(const Point3D&  p1,
                 const Vector3D& dir1,
                 const Point3D&  p2,
                 const Vector3D& dir2);
