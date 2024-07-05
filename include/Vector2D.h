#pragma once

#include <immintrin.h>

struct Vector2D
{
  // Rule of 5
  Vector2D();                     // default constructor
  Vector2D(double _x, double _y); // special constructor
  Vector2D(__m128d newVector);
  Vector2D(const Vector2D& other)            = default; // copy constructor
  Vector2D(Vector2D&& other)                 = default; // move constructor
  Vector2D& operator=(const Vector2D& other) = default; // move assignment
  ~Vector2D()                                = default; // deconstructor

  // accessing variables with indicies
  double&       operator[](int i);
  const double& operator[](int i) const;

  // math operator overloads
  Vector2D& operator*=(double s);
  Vector2D& operator/=(double s);
  Vector2D& operator+=(const Vector2D& v);
  Vector2D& operator-=(const Vector2D& v);

  double Magnitude();
  void   Normalize();

  double  x, y;
  double  v_ptr[2];
  __m128d _vector;

private:
  void SetVariables();
};

inline Vector2D
operator*(const Vector2D& v, double s)
{
  return Vector2D(_mm_mul_pd(v._vector, _mm_set1_pd(s)));
}

inline Vector2D
operator/(const Vector2D& v, double s)
{
  if (s == 0.0)
    return v;

  return Vector2D(_mm_div_pd(v._vector, _mm_set1_pd(s)));
}

inline Vector2D
operator-(const Vector2D& v)
{
  return Vector2D(_mm_mul_pd(v._vector, _mm_set1_pd(-1.0)));
}

inline Vector2D
operator+(const Vector2D& a, const Vector2D& b)
{
  return Vector2D(_mm_add_pd(a._vector, b._vector));
}

inline Vector2D
operator-(const Vector2D& a, const Vector2D& b)
{
  return Vector2D(_mm_sub_pd(a._vector, b._vector));
}

inline double
Magnitude(const Vector2D& v)
{
  double  tempPtr[2];
  __m128d temp = _mm_set1_pd(v.x * v.x + v.y * v.y);
  _mm_store_pd(tempPtr, _mm_sqrt_pd(temp));
  return tempPtr[0];
}

inline Vector2D
Normalize(const Vector2D& v)
{
  if (Magnitude(v) == 0.0)
    return v;

  return (v / Magnitude(v));
}

inline double
Dot(const Vector2D& a, const Vector2D& b)
{
  double  tempPtr[2];
  __m128d temp = _mm_mul_pd(a._vector, b._vector);
  _mm_store_pd(tempPtr, temp);
  return tempPtr[0] + tempPtr[1];
}