#pragma once

#include <cmath>
#include <immintrin.h>

struct Vector4D
{
  // Rule of 5
  Vector4D(); // default constructor
  Vector4D(double _x, double _y, double _z,
           double _w);                                  // special constructor
  Vector4D(__m256d newVector);                          // special constructor
  Vector4D(const Vector4D& other)            = default; // copy constructor
  Vector4D(Vector4D&& other)                 = default; // move constructor
  Vector4D& operator=(const Vector4D& other) = default; // move assignment
  ~Vector4D()                                = default; // deconstructor

  void GetFloatArray(float* arr);

  // accessing variables with indicies
  double&       operator[](int i);
  const double& operator[](int i) const;

  // math operator overloads
  Vector4D& operator*=(double s);
  Vector4D& operator/=(double s);
  Vector4D& operator+=(const Vector4D& v);
  Vector4D& operator-=(const Vector4D& v);

  double Magnitude();
  void   Normalize();

  double  x, y, z, w;
  double  v_ptr[4];
  __m256d _vector;

private:
  void SetVariables();
};

inline Vector4D
operator*(const Vector4D& v, double s)
{
  return Vector4D(_mm256_mul_pd(v._vector, _mm256_set1_pd(s)));
}

inline Vector4D
operator/(const Vector4D& v, double s)
{
  if (s == 0.0)
    return v;

  return Vector4D(_mm256_mul_pd(v._vector, _mm256_set1_pd(1.0 / s)));
}

inline Vector4D
operator-(const Vector4D& v)
{
  return Vector4D(_mm256_mul_pd(v._vector, _mm256_set1_pd(-1.0)));
}

inline Vector4D
operator+(const Vector4D& a, const Vector4D& b)
{
  return Vector4D(_mm256_add_pd(a._vector, b._vector));
}

inline Vector4D
operator-(const Vector4D& a, const Vector4D& b)
{
  return Vector4D(_mm256_sub_pd(a._vector, b._vector));
}

inline double
Magnitude(const Vector4D& v)
{
  double  tempPtr[4];
  __m256d vec2 = _mm256_mul_pd(v._vector, v._vector);
  vec2         = _mm256_hadd_pd(vec2, vec2);
  _mm256_store_pd(tempPtr, _mm256_sqrt_pd(vec2));
  return tempPtr[0] + tempPtr[2];
}

inline Vector4D
Normalize(const Vector4D& v)
{
  return (v / Magnitude(v));
}

inline double
Dot(const Vector4D& a, const Vector4D& b)
{
  double  tempPtr[4];
  __m256d vec2 = _mm256_mul_pd(a._vector, b._vector);
  vec2         = _mm256_hadd_pd(vec2, vec2);
  _mm256_store_pd(tempPtr, vec2);
  return tempPtr[0] + tempPtr[2];
}

inline Vector4D
Project(const Vector4D& a, const Vector4D& b)
{
  return (b * (Dot(a, b) / Dot(b, b)));
}

inline Vector4D
Reject(const Vector4D& a, const Vector4D& b)
{
  return (a - b * (Dot(a, b) / Dot(b, b)));
}
