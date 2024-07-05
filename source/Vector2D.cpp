#include "Vector2D.h"
#include <iostream>

Vector2D::Vector2D()
{
  x        = 0.0;
  y        = 0.0;
  v_ptr[0] = x;
  v_ptr[1] = y;
  _vector  = _mm_set1_pd(0.0);
}

Vector2D::Vector2D(double _x, double _y)
{
  x        = _x;
  y        = _y;
  v_ptr[0] = x;
  v_ptr[1] = y;
  _vector  = _mm_set_pd(y, x);
}

Vector2D::Vector2D(__m128d newVector)
{
  _vector = newVector;
  SetVariables();
}

void
Vector2D::GetFloatArray(float* arr)
{
  arr[0] = static_cast<float>(v_ptr[0]);
  arr[1] = static_cast<float>(v_ptr[1]);
}

double&
Vector2D::operator[](int i)
{
  return (v_ptr[i]);
}

const double&
Vector2D::operator[](int i) const
{
  return v_ptr[i];
}

Vector2D&
Vector2D::operator*=(double s)
{
  __m128d temp = _mm_set1_pd(s);
  _vector      = _mm_mul_pd(_vector, temp);
  SetVariables();
  return (*this);
}

Vector2D&
Vector2D::operator/=(double s)
{
  if (s == 0.0)
    return (*this);

  __m128d temp = _mm_set1_pd(s);
  _vector      = _mm_div_pd(_vector, temp);
  SetVariables();
  return (*this);
}

Vector2D&
Vector2D::operator+=(const Vector2D& v)
{
  _vector = _mm_add_pd(_vector, v._vector);
  SetVariables();
  return (*this);
}

Vector2D&
Vector2D::operator-=(const Vector2D& v)
{
  _vector = _mm_sub_pd(_vector, v._vector);
  SetVariables();
  return (*this);
}

double
Vector2D::Magnitude()
{
  double  tempPtr[2];
  __m128d temp = _mm_set1_pd(x * x + y * y);
  _mm_store_pd(tempPtr, _mm_sqrt_pd(temp));
  return tempPtr[0];
}

void
Vector2D::Normalize()
{
  if (Magnitude() == 0)
    return;

  _vector = _mm_div_pd(_vector, _mm_set1_pd(Magnitude()));
  SetVariables();
}

void
Vector2D::SetVariables()
{
  double tempPtr[2];
  _mm_store_pd(tempPtr, _vector);
  v_ptr[0] = tempPtr[0];
  v_ptr[1] = tempPtr[1];
  x        = v_ptr[0];
  y        = v_ptr[1];
}
