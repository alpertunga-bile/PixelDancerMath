#include "Vector2D.h"

Vector2D::Vector2D()
{
  _vector = _mm_setzero_pd();
}

Vector2D::Vector2D(double val)
{
  _vector = _mm_set1_pd(val);
}

Vector2D::Vector2D(double _x, double _y)
{
  _vector = _mm_set_pd(_y, _x);
}

Vector2D::Vector2D(__m128d newVector)
{
  _vector = newVector;
}

double&
Vector2D::operator[](int i)
{
  return _vector.m128d_f64[i];
}

const double&
Vector2D::operator[](int i) const
{
  return _vector.m128d_f64[i];
}

Vector2D&
Vector2D::operator*=(double s)
{
  __m128d temp = _mm_set1_pd(s);
  _vector      = _mm_mul_pd(_vector, temp);
  return (*this);
}

Vector2D&
Vector2D::operator/=(double s)
{
  if (s == 0.0)
    return (*this);

  __m128d temp = _mm_set1_pd(s);
  _vector      = _mm_div_pd(_vector, temp);
  return (*this);
}

Vector2D&
Vector2D::operator+=(const Vector2D& v)
{
  _vector = _mm_add_pd(_vector, v._vector);
  return (*this);
}

Vector2D&
Vector2D::operator-=(const Vector2D& v)
{
  _vector = _mm_sub_pd(_vector, v._vector);
  return (*this);
}

double
Vector2D::Magnitude()
{
  __m128d temp = _mm_set1_pd(x * x + y * y);
  temp         = _mm_sqrt_pd(temp);
  return temp.m128d_f64[0];
}

void
Vector2D::Normalize()
{
  if (Magnitude() == 0)
    return;

  _vector = _mm_div_pd(_vector, _mm_set1_pd(Magnitude()));
}
