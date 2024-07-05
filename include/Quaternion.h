#pragma once

#include "Matrix3D.h"

struct Quaternion
{
  Quaternion() = default; // default constructor
  Quaternion(double a, double b, double c, double d);
  Quaternion(const Vector3D& _v, double s);
  Quaternion(const Quaternion& other)            = default; // copy constructor
  Quaternion(Quaternion&& other)                 = default; // move constructor
  Quaternion& operator=(const Quaternion& other) = default; // move assignment
  ~Quaternion()                                  = default; // deconstructor

  Matrix3D GetRotationMatrix();
  void     SetRotationMatrix(const Matrix3D& m);

  Vector3D v;
  double   w = 0.0;
};

inline Quaternion
operator*(const Quaternion& q1, const Quaternion& q2)
{
  return Quaternion(Cross(q1.v, q2.v) + q2.v * q1.w + q1.v * q2.w,
                    q1.w * q2.w - Dot(q1.v, q2.v));
}

inline Vector3D
Transform(const Vector3D& v, const Quaternion& q)
{
  const Vector3D& b  = q.v;
  double          b2 = Dot(b, b);
  return (v * (q.w * q.w - b2) + b * (Dot(v, b) * 2.0) +
          Cross(b, v) * (q.w * 2.0));
}