#pragma once

struct Matrix4D;

#include "Vector3D.h"

// column based matrix
struct Matrix3D
{
  // Rule of 5
  Matrix3D() = default; // default constructor
  Matrix3D(double n00,
           double n01,
           double n02,
           double n10,
           double n11,
           double n12,
           double n20,
           double n21,
           double n22); // special constructor
  Matrix3D(const Vector3D& a,
           const Vector3D& b,
           const Vector3D& c); // special constructor
  Matrix3D(const Matrix4D& fromMat);
  Matrix3D(const Matrix3D& other)            = default; // copy constructor
  Matrix3D(Matrix3D&& other)                 = default; // move constructor
  Matrix3D& operator=(const Matrix3D& other) = default; // move assignment
  ~Matrix3D()                                = default; // deconstructor

  double& operator()(int i, int j) { return (m[j * 3 + i]); }

  const double& operator()(int i, int j) const { return (m[j * 3 + i]); }

  // access the jth column
  Vector3D operator[](int j) { return Vector3D(m[j + 0], m[j + 3], m[j + 6]); }

  // access the jth column
  const Vector3D operator[](int j) const
  {
    return Vector3D(m[j + 0], m[j + 3], m[j + 6]);
  }

  double m[9];
};

inline Matrix3D
operator+(Matrix3D mA, Matrix3D mB)
{
  Vector3D a = mA[0] + mB[0];
  Vector3D b = mA[1] + mB[1];
  Vector3D c = mA[2] + mB[2];

  return Matrix3D(a, b, c);
}

inline Matrix3D
operator-(Matrix3D mA, Matrix3D mB)
{
  Vector3D a = mA[0] - mB[0];
  Vector3D b = mA[1] - mB[1];
  Vector3D c = mA[2] - mB[2];

  return Matrix3D(a, b, c);
}

inline Matrix3D
operator*(Matrix3D matrix, double scalar)
{
  Vector3D a = matrix[0] * scalar;
  Vector3D b = matrix[1] * scalar;
  Vector3D c = matrix[2] * scalar;

  return Matrix3D(a, b, c);
}

inline Matrix3D
operator*(const Matrix3D& a, const Matrix3D b)
{
  return Matrix3D(a(0, 0) * b(0, 0) + a(0, 1) * b(1, 0) + a(0, 2) * b(2, 0),
                  a(0, 0) * b(0, 1) + a(0, 1) * b(1, 1) + a(0, 2) * b(2, 1),
                  a(0, 0) * b(0, 2) + a(0, 1) * b(1, 2) + a(0, 2) * b(2, 2),

                  a(1, 0) * b(0, 0) + a(1, 1) * b(1, 0) + a(1, 2) * b(2, 0),
                  a(1, 0) * b(0, 1) + a(1, 1) * b(1, 1) + a(1, 2) * b(2, 1),
                  a(1, 0) * b(0, 2) + a(1, 1) * b(1, 2) + a(1, 2) * b(2, 2),

                  a(2, 0) * b(0, 0) + a(2, 1) * b(1, 0) + a(2, 2) * b(2, 0),
                  a(2, 0) * b(0, 1) + a(2, 1) * b(1, 1) + a(2, 2) * b(2, 1),
                  a(2, 0) * b(0, 2) + a(2, 1) * b(1, 2) + a(2, 2) * b(2, 2));
}

inline Vector3D
operator*(const Matrix3D& m, const Vector3D& v)
{
  return Vector3D(m(0, 0) * v.x + m(0, 1) * v.y + m(0, 2) * v.z,
                  m(1, 0) * v.x + m(1, 1) * v.y + m(1, 2) * v.z,
                  m(2, 0) * v.x + m(2, 1) * v.y + m(2, 2) * v.z);
}

inline double
Determinant(const Matrix3D& m)
{
  return (m(0, 0) * (m(1, 1) * m(2, 2) - m(1, 2) * m(2, 1)) +
          m(0, 1) * (m(1, 2) * m(2, 0) - m(1, 0) * m(2, 2)) +
          m(0, 2) * (m(1, 0) * m(2, 1) - m(1, 1) * m(2, 0)));
}

inline Matrix3D
Transpose(const Matrix3D& m)
{
  return Matrix3D(m(0, 0),
                  m(1, 0),
                  m(2, 0),
                  m(0, 1),
                  m(1, 1),
                  m(2, 1),
                  m(0, 2),
                  m(1, 2),
                  m(2, 2));
}

inline Matrix3D
Inverse(const Matrix3D& m)
{
  double det = Determinant(m);

  if (det == 0)
    return Matrix3D();

  const Vector3D a = m[0];
  const Vector3D b = m[1];
  const Vector3D c = m[2];

  Vector3D row0 = Cross(b, c);
  Vector3D row1 = Cross(c, a);
  Vector3D row2 = Cross(a, b);

  double invDet = 1.0f / Dot(row2, c);

  return Matrix3D(row0 * invDet, row1 * invDet, row2 * invDet);
}