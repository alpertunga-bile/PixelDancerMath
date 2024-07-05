#include "Vector4D.h"

Vector4D::Vector4D()
{
  x        = 0.0f;
  y        = 0.0f;
  z        = 0.0f;
  w        = 0.0f;
  v_ptr[0] = x;
  v_ptr[1] = y;
  v_ptr[2] = z;
  v_ptr[3] = w;
  _vector  = _mm256_set1_pd(0.0f);
}

Vector4D::Vector4D(double _x, double _y, double _z, double _w)
{
  x        = _x;
  y        = _y;
  z        = _z;
  w        = _w;
  v_ptr[0] = x;
  v_ptr[1] = y;
  v_ptr[2] = z;
  v_ptr[3] = w;
  _vector  = _mm256_load_pd(v_ptr);
}

Vector4D::Vector4D(__m256d newVector)
{
  _vector = newVector;
  SetVariables();
}

void
Vector4D::GetArray(double* arr)
{
  std::memcpy(arr, v_ptr, 4 * sizeof(double));
}

double&
Vector4D::operator[](int i)
{
  return (v_ptr[i]);
}

const double&
Vector4D::operator[](int i) const
{
  return (v_ptr[i]);
}

Vector4D&
Vector4D::operator*=(double s)
{
  _vector = _mm256_mul_pd(_vector, _mm256_set1_pd(s));
  SetVariables();
  return (*this);
}

Vector4D&
Vector4D::operator/=(double s)
{
  if (s == 0.0)
    return (*this);

  _vector = _mm256_mul_pd(_vector, _mm256_set1_pd(1.0 / s));
  SetVariables();
  return (*this);
}

Vector4D&
Vector4D::operator+=(const Vector4D& v)
{
  _vector = _mm256_add_pd(_vector, v._vector);
  SetVariables();
  return (*this);
}

Vector4D&
Vector4D::operator-=(const Vector4D& v)
{
  _vector = _mm256_sub_pd(_vector, v._vector);
  SetVariables();
  return (*this);
}

double
Vector4D::Magnitude()
{
  double  tempPtr[4];
  __m256d vec2 = _mm256_mul_pd(_vector, _vector);
  vec2         = _mm256_hadd_pd(vec2, vec2);
  _mm256_store_pd(tempPtr, _mm256_sqrt_pd(vec2));
  return tempPtr[0] + tempPtr[2];
}

void
Vector4D::Normalize()
{
  (*this) /= Magnitude();
}

void
Vector4D::SetVariables()
{
  _mm256_store_pd(v_ptr, _vector);
  x = v_ptr[0];
  y = v_ptr[1];
  z = v_ptr[2];
  w = v_ptr[3];
}
