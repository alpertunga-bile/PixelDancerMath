#pragma once

#include "Transform4D.h"

struct Plane
{
  // Rule of 5
  Plane() = default; // default constructor
  Plane(double _x, double _y, double _z, double _w)
    : x(_x)
    , y(_y)
    , z(_z)
    , w(_w){}; // special constructor
  Plane(const Vector3D& n, double d)
    : x(n.x)
    , y(n.y)
    , z(n.z)
    , w(d)
  {
  } // special constructor
  Plane(const Plane& other)            = default; // copy constructor
  Plane(Plane&& other)                 = default; // move constructor
  Plane& operator=(const Plane& other) = default; // move assignment
  ~Plane()                             = default; // deconstructor

  inline const Vector3D GetNormal() const { return Vector3D(x, y, z); }

  double x, y, z, w;
};

inline Plane
operator*(const Plane& f, const Transform4D& h)
{
  return Plane(f.x * h(0, 0) + f.y * h(1, 0) + f.z * h(2, 0),
               f.x * h(0, 1) + f.y * h(1, 1) + f.z * h(2, 1),
               f.x * h(0, 2) + f.y * h(1, 2) + f.z * h(2, 2),
               f.x * h(0, 3) + f.y * h(1, 3) + f.z * h(2, 3) + f.w);
}

inline double
Dot(const Plane& f, const Vector3D& v)
{
  return (f.x * v.x + f.y * v.y + f.z * v.z);
}

inline double
Dot(const Plane& f, const Point3D& p)
{
  return (f.x * p.x + f.y * p.y + f.z * p.z + f.w);
}

bool
IntersectLinePlane(const Point3D&  p,
                   const Vector3D& dir,
                   const Plane&    f,
                   Point3D&        q);
Transform4D
MakeReflection(const Plane& f);
bool
IntersectThreePlanes(const Plane& f1,
                     const Plane& f2,
                     const Plane& f3,
                     Point3D&     p);
bool
IntersectTwoPlanes(const Plane& f1, const Plane& f2, Point3D& p, Vector3D& v);