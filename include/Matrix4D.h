#pragma once

#include "Vector3D.h"
#include "Vector4D.h"

// column based matrix
struct Matrix4D
{
  // Rule of 5
  Matrix4D() = default; // default constructor
  Matrix4D(double n00,
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
           double n23,
           double n30,
           double n31,
           double n32,
           double n33); // special constructor
  Matrix4D(const Vector4D& a,
           const Vector4D& b,
           const Vector4D& c,
           const Vector4D& d);                          // special constructor
  Matrix4D(const Matrix4D& other)            = default; // copy constructor
  Matrix4D(Matrix4D&& other)                 = default; // move constructor
  Matrix4D& operator=(const Matrix4D& other) = default; // move assignment
  ~Matrix4D()                                = default; // deconstructor

  double& operator()(int i, int j) { return (m[j * 4 + i]); }

  const double& operator()(int i, int j) const { return (m[j * 4 + i]); }

  // access the jth column
  Vector4D operator[](int j)
  {
    return Vector4D(m[j + 0], m[j + 4], m[j + 8], m[j + 12]);
  }

  // access the jth column
  const Vector4D operator[](int j) const
  {
    return Vector4D(m[j + 0], m[j + 4], m[j + 8], m[j + 12]);
  }

  double m[16];
};

inline Matrix4D
operator+(Matrix4D mA, Matrix4D mB)
{
  Vector4D a = mA[0] + mB[0];
  Vector4D b = mA[1] + mB[1];
  Vector4D c = mA[2] + mB[2];
  Vector4D d = mA[3] + mB[3];

  return Matrix4D(a, b, c, d);
}

inline Matrix4D
operator-(Matrix4D mA, Matrix4D mB)
{
  Vector4D a = mA[0] - mB[0];
  Vector4D b = mA[1] - mB[1];
  Vector4D c = mA[2] - mB[2];
  Vector4D d = mA[3] - mB[3];

  return Matrix4D(a, b, c, d);
}

inline Matrix4D
operator*(Matrix4D matrix, double scalar)
{
  Vector4D a = matrix[0] * scalar;
  Vector4D b = matrix[1] * scalar;
  Vector4D c = matrix[2] * scalar;
  Vector4D d = matrix[3] * scalar;

  return Matrix4D(a, b, c, d);
}

inline Matrix4D
operator*(const Matrix4D& a, const Matrix4D b)
{
  return Matrix4D(a(0, 0) * b(0, 0) + a(0, 1) * b(1, 0) + a(0, 2) * b(2, 0) +
                    a(0, 3) * b(3, 0),
                  a(0, 0) * b(0, 1) + a(0, 1) * b(1, 1) + a(0, 2) * b(2, 1) +
                    a(0, 3) * b(3, 1),
                  a(0, 0) * b(0, 2) + a(0, 1) * b(1, 2) + a(0, 2) * b(2, 2) +
                    a(0, 3) * b(3, 2),
                  a(0, 0) * b(0, 3) + a(0, 1) * b(1, 3) + a(0, 2) * b(2, 3) +
                    a(0, 3) * b(3, 3),

                  a(1, 0) * b(0, 0) + a(1, 1) * b(1, 0) + a(1, 2) * b(2, 0) +
                    a(1, 3) * b(3, 0),
                  a(1, 0) * b(0, 1) + a(1, 1) * b(1, 1) + a(1, 2) * b(2, 1) +
                    a(1, 3) * b(3, 1),
                  a(1, 0) * b(0, 2) + a(1, 1) * b(1, 2) + a(1, 2) * b(2, 2) +
                    a(1, 3) * b(3, 2),
                  a(1, 0) * b(0, 3) + a(1, 1) * b(1, 3) + a(1, 2) * b(2, 3) +
                    a(1, 3) * b(3, 3),

                  a(2, 0) * b(0, 0) + a(2, 1) * b(1, 0) + a(2, 2) * b(2, 0) +
                    a(2, 3) * b(3, 0),
                  a(2, 0) * b(0, 1) + a(2, 1) * b(1, 1) + a(2, 2) * b(2, 1) +
                    a(2, 3) * b(3, 1),
                  a(2, 0) * b(0, 2) + a(2, 1) * b(1, 2) + a(2, 2) * b(2, 2) +
                    a(2, 3) * b(3, 2),
                  a(2, 0) * b(0, 3) + a(2, 1) * b(1, 3) + a(2, 2) * b(2, 3) +
                    a(2, 3) * b(3, 3),

                  a(3, 0) * b(0, 0) + a(3, 1) * b(1, 0) + a(3, 2) * b(2, 0) +
                    a(3, 3) * b(3, 0),
                  a(3, 0) * b(0, 1) + a(3, 1) * b(1, 1) + a(3, 2) * b(2, 1) +
                    a(3, 3) * b(3, 1),
                  a(3, 0) * b(0, 2) + a(3, 1) * b(1, 2) + a(3, 2) * b(2, 2) +
                    a(3, 3) * b(3, 2),
                  a(3, 0) * b(0, 3) + a(3, 1) * b(1, 3) + a(3, 2) * b(2, 3) +
                    a(3, 3) * b(3, 3));
}

inline Vector4D
operator*(const Matrix4D& m, const Vector4D& v)
{
  return Vector4D(m(0, 0) * v.x + m(0, 1) * v.y + m(0, 2) * v.z + m(0, 3) * v.w,
                  m(1, 0) * v.x + m(1, 1) * v.y + m(1, 2) * v.z + m(1, 3) * v.w,
                  m(2, 0) * v.x + m(2, 1) * v.y + m(2, 2) * v.z + m(2, 3) * v.w,
                  m(3, 0) * v.x + m(3, 1) * v.y + m(3, 2) * v.z +
                    m(3, 3) * v.w);
}

inline Matrix4D
Transpose(const Matrix4D& m)
{
  return Matrix4D(m(0, 0),
                  m(1, 0),
                  m(2, 0),
                  m(3, 0),
                  m(0, 1),
                  m(1, 1),
                  m(2, 1),
                  m(3, 1),
                  m(0, 2),
                  m(1, 2),
                  m(2, 2),
                  m(3, 2),
                  m(0, 3),
                  m(1, 3),
                  m(2, 3),
                  m(3, 3));
}

inline Matrix4D
Inverse(const Matrix4D& m)
{
  const Vector3D a = Vector3D(m[0].x, m[0].y, m[0].z);
  const Vector3D b = Vector3D(m[1].x, m[1].y, m[1].z);
  const Vector3D c = Vector3D(m[2].x, m[2].y, m[2].z);
  const Vector3D d = Vector3D(m[3].x, m[3].y, m[3].z);

  const double x = m(3, 0);
  const double y = m(3, 1);
  const double z = m(3, 2);
  const double w = m(3, 3);

  Vector3D s = Cross(a, b);
  Vector3D t = Cross(c, d);
  Vector3D u = a * y - b * x;
  Vector3D v = c * w - d * x;

  double det = (Dot(s, v) + Dot(t, u));
  if (det == 0)
    return Matrix4D();

  double invDet  = 1.0f / det;
  s             *= invDet;
  t             *= invDet;
  u             *= invDet;
  v             *= invDet;

  Vector3D row0 = Cross(b, v) + t * y;
  Vector3D row1 = Cross(v, a) - t * x;
  Vector3D row2 = Cross(d, u) + s * w;
  Vector3D row3 = Cross(u, c) - s * z;

  return Matrix4D(row0.x,
                  row0.y,
                  row0.z,
                  -Dot(b, t),
                  row1.x,
                  row1.y,
                  row1.z,
                  Dot(a, t),
                  row2.x,
                  row2.y,
                  row2.z,
                  -Dot(d, s),
                  row3.x,
                  row3.y,
                  row3.z,
                  Dot(c, s));
}