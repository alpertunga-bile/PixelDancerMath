#pragma once

#include <immintrin.h>

struct Vector3D
{
  union
  {
    struct
    {
      __m256d _vector;
    };

    struct
    {
      double x, y, z;
    };
  };

  // Rule of 5
  Vector3D();                                           // default constructor
  Vector3D(double val);                                 // special constructor
  Vector3D(double _x, double _y, double _z);            // special constructor
  Vector3D(__m256d newVector);                          // special constructor
  Vector3D(const Vector3D& other)            = default; // copy constructor
  Vector3D(Vector3D&& other)                 = default; // move constructor
  Vector3D& operator=(const Vector3D& other) = default; // move assignment
  ~Vector3D()                                = default; // deconstructor

  // accessing variables with indicies
  double&       operator[](int i);
  const double& operator[](int i) const;

  // math operator overloads
  Vector3D& operator*=(double s);
  Vector3D& operator/=(double s);
  Vector3D& operator+=(const Vector3D& v);
  Vector3D& operator-=(const Vector3D& v);

  double Magnitude();
  void   Normalize();
};

inline Vector3D
operator*(const Vector3D& v, double s)
{
  return Vector3D(_mm256_mul_pd(v._vector, _mm256_set1_pd(s)));
}

inline Vector3D
operator/(const Vector3D& v, double s)
{
  if (s == 0.0)
    return v;

  return Vector3D(_mm256_mul_pd(v._vector, _mm256_set1_pd(1.0 / s)));
}

inline Vector3D
operator-(const Vector3D& v)
{
  return Vector3D(_mm256_mul_pd(v._vector, _mm256_set1_pd(-1.0)));
}

inline Vector3D
operator+(const Vector3D& a, const Vector3D& b)
{
  return Vector3D(_mm256_add_pd(a._vector, b._vector));
}

inline Vector3D
operator-(const Vector3D& a, const Vector3D& b)
{
  return Vector3D(_mm256_sub_pd(a._vector, b._vector));
}

inline double
Magnitude(const Vector3D& v)
{
  __m256d temp = _mm256_set1_pd(v.x * v.x + v.y * v.y + v.z * v.z);
  temp         = _mm256_sqrt_pd(temp);
  return temp.m256d_f64[0];
}

inline Vector3D
Normalize(const Vector3D& v)
{
  return (v / Magnitude(v));
}

inline double
Dot(const Vector3D& a, const Vector3D& b)
{
  __m256d xy = _mm256_mul_pd(a._vector, b._vector);
  xy         = _mm256_hadd_pd(xy, xy);
  return xy.m256d_f64[0] + xy.m256d_f64[2];
}

inline Vector3D
Cross(const Vector3D& a, const Vector3D& b)
{
  return Vector3D(
    a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}

inline Vector3D
Project(const Vector3D& a, const Vector3D& b)
{
  return (b * (Dot(a, b) / Dot(b, b)));
}

inline Vector3D
Reject(const Vector3D& a, const Vector3D& b)
{
  return (a - b * (Dot(a, b) / Dot(b, b)));
}