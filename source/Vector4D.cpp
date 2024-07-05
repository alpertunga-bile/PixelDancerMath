#include "Vector4D.h"

Vector4D::Vector4D()
{
  _vector = _mm256_setzero_pd();
}

Vector4D::Vector4D(double val)
{
  _vector = _mm256_set1_pd(val);
}

Vector4D::Vector4D(double _x, double _y, double _z, double _w)
{
  _vector = _mm256_set_pd(_w, _z, _y, _x);
}

Vector4D::Vector4D(__m256d newVector)
{
  _vector = newVector;
}

double&
Vector4D::operator[](int i)
{
  return _vector.m256d_f64[i];
}

const double
Vector4D::operator[](int i) const
{
  return _vector.m256d_f64[i];
}

Vector4D&
Vector4D::operator*=(double s)
{
  _vector = _mm256_mul_pd(_vector, _mm256_set1_pd(s));
  return (*this);
}

Vector4D&
Vector4D::operator/=(double s)
{
  if (s == 0.0)
    return (*this);

  _vector = _mm256_mul_pd(_vector, _mm256_set1_pd(1.0 / s));
  return (*this);
}

Vector4D&
Vector4D::operator+=(const Vector4D& v)
{
  _vector = _mm256_add_pd(_vector, v._vector);
  return (*this);
}

Vector4D&
Vector4D::operator-=(const Vector4D& v)
{
  _vector = _mm256_sub_pd(_vector, v._vector);
  return (*this);
}

double
Vector4D::Magnitude()
{
  __m256d vec2 = _mm256_mul_pd(_vector, _vector);
  vec2         = _mm256_hadd_pd(vec2, vec2);
  vec2         = _mm256_sqrt_pd(vec2);
  return vec2.m256d_f64[0] + vec2.m256d_f64[2];
}

void
Vector4D::Normalize()
{
  (*this) /= Magnitude();
}