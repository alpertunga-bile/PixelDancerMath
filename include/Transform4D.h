#pragma once

#include "Matrix4D.h"
#include "Point3D.h"

struct Transform4D : Matrix4D
{
  // Rule of 5
  Transform4D() = default; // default constructor
  Transform4D(double n00,
              double n01,
              double n02,
              double n03,
              double n10,
              double n11,
              double n12,
              double n13,
              double n20,
              double n21,
              double n22,
              double n23); // special constructor
  Transform4D(const Vector3D& a,
              const Vector3D& b,
              const Vector3D& c,
              const Point3D&  d);                   // special constructor
  Transform4D(const Transform4D& other) = default; // copy constructor
  Transform4D(Transform4D&& other)      = default; // move constructor
  Transform4D& operator=(const Transform4D& other) = default; // move assignment
  ~Transform4D()                                   = default; // deconstructor

  const Point3D GetTranslation() const { return Point3D(m[3], m[7], m[11]); }

  void SetTranslation(const Point3D& p)
  {
    m[3]  = p.x;
    m[7]  = p.y;
    m[11] = p.z;
  }

  // access the jth column
  Vector3D operator[](int j) { return Vector3D(m[j + 0], m[j + 4], m[j + 8]); }

  // access the jth column
  const Vector3D operator[](int j) const
  {
    return Vector3D(m[j + 0], m[j + 4], m[j + 8]);
  }
};

inline Transform4D
Inverse(const Transform4D& tf)
{
  const Vector3D& a = tf[0];
  const Vector3D& b = tf[1];
  const Vector3D& c = tf[2];
  const Vector3D& d = tf[3];

  Vector3D s = Cross(a, b);
  Vector3D t = Cross(c, d);

  double invDet = 1.0f / Dot(s, c);

  s          *= invDet;
  t          *= invDet;
  Vector3D v  = c * invDet;

  Vector3D r0 = Cross(b, v);
  Vector3D r1 = Cross(v, a);

  return Transform4D(r0.x,
                     r0.y,
                     r0.z,
                     -Dot(b, t),
                     r1.x,
                     r1.y,
                     r1.z,
                     -Dot(a, t),
                     s.x,
                     s.y,
                     s.z,
                     -Dot(d, s));
}

inline Transform4D
operator*(const Transform4D& a, const Transform4D& b)
{
  return Transform4D(
    a(0, 0) * b(0, 0) + a(0, 1) * b(1, 0) + a(0, 2) * b(2, 0),
    a(0, 0) * b(0, 1) + a(0, 1) * b(1, 1) + a(0, 2) * b(2, 1),
    a(0, 0) * b(0, 2) + a(0, 1) * b(1, 2) + a(0, 2) * b(2, 2),
    a(0, 0) * b(0, 3) + a(0, 1) * b(1, 3) + a(0, 2) * b(2, 3) + a(0, 3),

    a(1, 0) * b(0, 0) + a(1, 1) * b(1, 0) + a(1, 2) * b(2, 0),
    a(1, 0) * b(0, 1) + a(1, 1) * b(1, 1) + a(1, 2) * b(2, 1),
    a(1, 0) * b(0, 2) + a(1, 1) * b(1, 2) + a(1, 2) * b(2, 2),
    a(1, 0) * b(0, 3) + a(1, 1) * b(1, 3) + a(1, 2) * b(2, 3) + a(1, 3),

    a(2, 0) * b(0, 0) + a(2, 1) * b(1, 0) + a(2, 2) * b(2, 0),
    a(2, 0) * b(0, 1) + a(2, 1) * b(1, 1) + a(2, 2) * b(2, 1),
    a(2, 0) * b(0, 2) + a(2, 1) * b(1, 2) + a(2, 2) * b(2, 2),
    a(2, 0) * b(0, 3) + a(2, 1) * b(1, 3) + a(2, 2) * b(2, 3) + a(2, 3));
}

inline Vector3D
operator*(const Transform4D& tf, const Vector3D& v)
{
  return Vector3D(tf(0, 0) * v.x + tf(0, 1) * v.y + tf(0, 2) * v.z,
                  tf(1, 0) * v.x + tf(1, 1) * v.y + tf(1, 2) * v.z,
                  tf(2, 0) * v.x + tf(2, 1) * v.y + tf(2, 2) * v.z);
}

inline Point3D
operator*(const Transform4D& tf, const Point3D& p)
{
  return Point3D(tf(0, 0) * p.x + tf(0, 1) * p.y + tf(0, 2) * p.z + tf(0, 3),
                 tf(1, 0) * p.x + tf(1, 1) * p.y + tf(1, 2) * p.z + tf(1, 3),
                 tf(2, 0) * p.x + tf(2, 1) * p.y + tf(2, 2) * p.z + tf(2, 3));
}

// Translate normal vector between coordinate systems
Vector3D
operator*(const Vector3D& n, const Transform4D& m)
{
  return Vector3D(n.x * m(0, 0) + n.y * m(1, 0) + n.z * m(2, 0),
                  n.x * m(0, 1) + n.y * m(1, 1) + n.z * m(2, 1),
                  n.x * m(0, 2) + n.y * m(1, 2) + n.z * m(2, 2));
}