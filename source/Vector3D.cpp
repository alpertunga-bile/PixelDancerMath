#include "Vector3D.h"

Vector3D::Vector3D()
{
  _vector = _mm256_setzero_pd();
}

Vector3D::Vector3D(double val)
{
  _vector = _mm256_set1_pd(val);
}

Vector3D::Vector3D(double _x, double _y, double _z)
{
  _vector = _mm256_set_pd(0.0, z, y, x);
}

Vector3D::Vector3D(__m256d newVector)
{
  _vector = newVector;
}

double&
Vector3D::operator[](int i)
{
  return _vector.m256d_f64[i];
}

const double&
Vector3D::operator[](int i) const
{
  return _vector.m256d_f64[i];
}

Vector3D&
Vector3D::operator*=(double s)
{
  __m256d temp = _mm256_set1_pd(s);
  _vector      = _mm256_mul_pd(_vector, temp);
  return (*this);
}

Vector3D&
Vector3D::operator/=(double s)
{
  if (s == 0.0)
    return (*this);

  __m256d temp = _mm256_set1_pd(1.0 / s);
  _vector      = _mm256_mul_pd(_vector, temp);
  return (*this);
}

Vector3D&
Vector3D::operator+=(const Vector3D& v)
{
  _vector = _mm256_add_pd(_vector, v._vector);
  return (*this);
}

Vector3D&
Vector3D::operator-=(const Vector3D& v)
{
  _vector = _mm256_sub_pd(_vector, v._vector);
  return (*this);
}

double
Vector3D::Magnitude()
{
  __m256d temp = _mm256_set1_pd(x * x + y * y + z * z);
  temp         = _mm256_sqrt_pd(temp);
  return temp.m256d_f64[0];
}

void
Vector3D::Normalize()
{
  if (Magnitude() == 0.0)
    return;

  _vector = _mm256_div_pd(_vector, _mm256_set1_pd(Magnitude()));
}