#pragma once

#include <immintrin.h>

struct Vector2D
{
  union
  {
    struct
    {
      __m128d _vector;
    };

    struct
    {
      double x, y;
    };
  };

  // Rule of 5
  Vector2D();                                           // default constructor
  Vector2D(double val);                                 // special constructor
  Vector2D(double _x, double _y);                       // special constructor
  Vector2D(__m128d newVector);                          // special constructor
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
  __m128d temp = _mm_set1_pd(v.x * v.x + v.y * v.y);
  temp         = _mm_sqrt_pd(temp);
  return temp.m128d_f64[0];
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
  __m128d temp = _mm_mul_pd(a._vector, b._vector);
  return temp.m128d_f64[0] + temp.m128d_f64[1];
}